#include "mPlate.h"


mPlate::mPlate()
{
	//this->parent = parent;
}

mPlate::~mPlate()
{
}

bool mPlate::recognize()
{
	bool success=SepratePlate();//将车牌图片分离进行前处理
	if (!success) return success;

	char   mainfold[MAX_PATH];
	getcwd(mainfold, MAX_PATH);//当前目录

	char *_chars2 = "\\train\\chars2";
	char *_charschinese = "\\train\\charsChinese";
	char *_model = "\\train\\MODEL";

	char chars2fold[MAX_PATH], charschinesefold[MAX_PATH], modelfold[MAX_PATH];

	strcpy(chars2fold, mainfold);
	strcpy(charschinesefold, mainfold);
	strcpy(modelfold, mainfold);

	strcat(chars2fold, _chars2);
	strcat(charschinesefold, _charschinese);
	strcat(modelfold, _model);

	//导入汉字，数字英文识别 卷积网络
	CNNTrain CNN_chars2(chars2fold, modelfold);
	CNN_chars2.loadModel("chars2");
	CNNTrain CNN_charsChinese(charschinesefold, modelfold);
	CNN_charsChinese.loadModel("charsChinese");


	std::vector<IplImage*>::iterator iter;
	iter = mCharImg.begin();
	std::string resChinese=CNN_charsChinese.Predict_Img(*iter);
	mPlateRes.push_back(resChinese);
	iter++;
	for (; iter != mCharImg.end(); iter++)
	{
		std::string reschar=CNN_chars2.Predict_Img(*iter);
		mPlateRes.push_back(reschar);
	}
	return true;
}

bool mPlate::SepratePlate()
{
	IplImage* PlateImgGray = cvCreateImage(cvGetSize(mPlateImg), IPL_DEPTH_8U, 1);
	grayScaleImage(mPlateImg, PlateImgGray);
	if (this->mPlateColor.pColor == Green || this->mPlateColor.pColor == Yellow || this->mPlateColor.pColor == White)
		antiImgColor(PlateImgGray, PlateImgGray);
	IplImage*Plate_threshold = cvCreateImage(cvGetSize(PlateImgGray), IPL_DEPTH_8U, 1);
	double ret = cvThreshold(PlateImgGray, Plate_threshold, 0, 255, CV_THRESH_OTSU + CV_THRESH_BINARY);

	int wavePeakH, wavePeakV;
	std::vector<mPoint> wavePeaksH, wavePeaksV;
	getWavePeak(PlateImgGray, wavePeakH, wavePeaksH, hoshorizon);
	getWavePeak(PlateImgGray, wavePeakV, wavePeaksV, vertical, 3);

	if (wavePeakH == 0) return false;
	if (wavePeakV<6) return false;
	
	mPoint waveH = mavWave(wavePeaksH);
	mPoint waveV = mavWave(wavePeaksV);
	// 认为水平方向，最大的波峰为车牌区域
	IplImage *imgCut1 = cvCreateImage(CvSize(Plate_threshold->width, waveH.y - waveH.x), IPL_DEPTH_8U, Plate_threshold->nChannels);
	cutImg(Plate_threshold, imgCut1, 0, Plate_threshold->width, waveH.x, waveH.y);
	
	int max_wave_dis = waveV.y - waveV.x;
	
	//判断是否是左侧车牌边缘, 为边缘则剔除
	if ((wavePeaksV[0].y - wavePeaksV[0].x) < (max_wave_dis / 3) && wavePeaksV[0].x == 0)
		wavePeaksV.erase(wavePeaksV.begin());
	
	// 组合分离汉字
	std::vector<mPoint>::iterator iter;
	int cur_dis = 0;
	int i = 0;
	for (iter = wavePeaksV.begin(); iter != wavePeaksV.end(); iter++)
	{
		if ((iter->y - iter->x + cur_dis) > (max_wave_dis * 0.6))
			break;
		else
		{
			cur_dis += iter->y - iter->x;
			i++;
		}
	}
	if (i!=0)
	{
		mPoint waveChinese; 
		waveChinese.x = wavePeaksV[0].x;
		waveChinese.y = wavePeaksV[i].y;
		wavePeaksV.erase(wavePeaksV.begin());
		
		wavePeaksV.insert(wavePeaksV.begin(), waveChinese);
	}
	
	//# 去除车牌上的分隔点
	mPoint point = wavePeaksV[2];
	if (point.y - point.x < max_wave_dis / 3)
	{
		IplImage* point_img = cvCreateImage(CvSize(point.y - point.x, imgCut1->height), IPL_DEPTH_8U, 1);
		cutImg(imgCut1, point_img, point.x, point.y, 0, imgCut1->height);
		if (meanImg(point_img) < (255. / 5.))
		{
			wavePeaksV.erase(wavePeaksV.begin() + 3);
		}	
	}
	if (wavePeaksV.size() <= 6)
		return false;

	//分离车牌
	for (iter = wavePeaksV.begin(); iter != wavePeaksV.end(); iter++)
	{
		IplImage* tempImg = cvCreateImage(CvSize(iter->y - iter->x, imgCut1->height), IPL_DEPTH_8U, 1);
		cutImg(imgCut1, tempImg, iter->x, iter->y, 0, imgCut1->height);
		double seed = 20./tempImg->height ;
		double seedy = 20./tempImg->width ;
		if (seedy < seed) seed = seedy;
		IplImage* resimg;
		resizeImgage(tempImg, resimg, seed, seed);
		IplImage* expimg = expandImage(resimg, 20, 20, 0);
		
		float imean = meanImg(expimg);
		if (imean <13.) continue;
		//if (meanImg(expimg) < (255. / 5.)) continue;
		mCharImg.push_back(expimg);
		//---------------------------------------
		//cvShowImage("name", expimg);
		//cvWaitKey();
		//---------------------------------------
	}
	if (mCharImg.size() <= 6)
		return false;
	return true;
}

mPoint mPlate::mavWave(vector<mPoint> &wavePeaks)
{
	mPoint wave;
	std::vector<mPoint>::iterator iter;
	wave= wavePeaks[0];
	for (iter= wavePeaks.begin(); iter != wavePeaks.end(); iter++)
	{
		if ((iter->y - iter->x) > (wave.y - wave.x))
			wave= *iter;
	}
	return wave;
}

std::string mPlate::getPlateString()
{ 
	std::vector<std::string>::iterator iter; 
	iter = mPlateRes.begin();
	std::string out;
	while (iter != mPlateRes.end())
	{
		out += *iter + " ";
		iter++;
	}
	return out;
}

