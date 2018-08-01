#include "mPlate_Locate.h"


mPlate_Locate::mPlate_Locate()
{}

mPlate_Locate::~mPlate_Locate()
{}

void mPlate_Locate::InitialData(IplImage *inImg)
{
	IplImage * _Img;
	int w_src = inImg->width;
	if (w_src > MAX_WIDTH)
	{
		double ResizeRate = double(MAX_WIDTH) / double(w_src);
		resizeImgage(inImg, _Img, ResizeRate, ResizeRate);
	}
	else
		_Img = inImg;
	gaussianBlurImage(_Img, initialImg, GAUSSIANBLUR_SIZE, 0);
	locateImg = cvCreateImage(cvGetSize(initialImg), IPL_DEPTH_8U, initialImg->nChannels);
	cvCopy(initialImg, locateImg);
}

int mPlate_Locate::LocatePlate()
{
	//vector<mPlate> candPlates;
	//candPlates.reserve(64);
	plateLocateBYColor(initialImg, candPlates, 1);

	plateLocateBYSobel(initialImg, candPlates, 1);

	vector<mPlate>::iterator iter;
	iter = candPlates.begin();
	while ( iter != candPlates.end())
	{
		//iter->plateShow();
		if (!(iter->recognize()))
			iter = candPlates.erase(iter);
		else
			iter++;
	}

	return 0;
}
//--------------------------------------------------------------------------------------------------------------

int mPlate_Locate::plateLocateBYColor(IplImage* src, vector<mPlate> &candPlates, int index) //int mPlate_Locate::plateLocateBYColor(IplImage* src, int index)
{
	//vector<mPlate> platesBlue, platesYellow;
	//vector<CvBox2D> rectsBlue, rectsYellow;
	//IplImage *ImageEdgeBlue, *ImageEdgeYellow;

	vector<mPlate> platesBlue, platesYellow, platesGreen, platesWhite;
	vector<CvBox2D> rectsBlue, rectsYellow, rectsGreen, rectsWhite;
	IplImage *ImageEdgeBlue, *ImageEdgeYellow, *ImageEdgeGreen, *ImageEdgeWhite;
	
#pragma omp parallel sections//并行计算
	{
#pragma omp section
	{
		colorSearch(src, Blue, ImageEdgeBlue, rectsBlue);
		obtainPlates(src, rectsBlue, platesBlue);
	}
#pragma omp section
	{
		colorSearch(src, Yellow, ImageEdgeYellow, rectsYellow);
		obtainPlates(src, rectsYellow, platesYellow);
	}
#pragma omp section
	{
		colorSearch(src, Green, ImageEdgeGreen, rectsGreen);
		obtainPlates(src, rectsGreen, platesGreen);
	}
#pragma omp section
	{
		colorSearch(src, White, ImageEdgeWhite, rectsWhite);
		obtainPlates(src, rectsWhite, platesWhite);
	}
	}
	/*
	vector<mPlate>::iterator iter;
	for (iter = platesBlue.begin(); iter != platesBlue.end(); iter++)
	{
		candPlates.push_back(*iter);
	}*/

	candPlates.insert(candPlates.end(), platesBlue.begin(), platesBlue.end());
	candPlates.insert(candPlates.end(), platesYellow.begin(), platesYellow.end());
	candPlates.insert(candPlates.end(), platesGreen.begin(), platesGreen.end());
	candPlates.insert(candPlates.end(), platesWhite.begin(), platesWhite.end());

	return 0;
}

int mPlate_Locate::colorSearch(const IplImage *src, const Colors r, IplImage* &out, vector<CvBox2D>  &outRects)
{
	IplImage * match_grey = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);

	// width is important to the final results;
	const int color_morph_width = 19;
	const int color_morph_height = 4;

	colorMatch(src, *match_grey, r, false);

	IplImage * src_threshold = cvCreateImage(cvGetSize(match_grey), IPL_DEPTH_8U, 1);;

	cvThreshold(match_grey, src_threshold, 0, 255, CV_THRESH_OTSU + CV_THRESH_BINARY);

	IplConvKernel* kernel = cvCreateStructuringElementEx(color_morph_width, color_morph_height,
		int(color_morph_width / 2), int(color_morph_height / 2), CV_SHAPE_RECT); //构建核

	cvMorphologyEx(src_threshold, src_threshold, NULL, kernel, CV_MOP_CLOSE, 1);

	out = src_threshold;

	//cvShowImage("pic", src_threshold);
	//cvWaitKey();

	outRects = getImageRect(src_threshold);

	return 0;
}

//--------------------------------------------------------------------------------------------------------------
int mPlate_Locate::plateLocateBYSobel(IplImage* src, vector<mPlate> &candPlates, int index) {
	
	vector<mPlate> platesSobel;
	vector<CvBox2D> rectSobel;

	sobelRectSearch(src, rectSobel);
	obtainPlates(src, rectSobel, platesSobel);

	candPlates.insert(candPlates.end(), platesSobel.begin(), platesSobel.end());

	return 0;
}

int mPlate_Locate::sobelRectSearch(const IplImage* src, vector<CvBox2D > &outRects) {
	IplImage * src_threshold;
	// width is important to the final results;
	const int sobel_morph_width = 19;
	const int sobel_morph_height = 5;
	sobelOper(src, src_threshold, sobel_morph_width, sobel_morph_height);

	//cvShowImage("pic", src_threshold);
	//cvWaitKey();

	outRects = getImageRect(src_threshold);
	return 0;
}

int mPlate_Locate::sobelOper(const IplImage*imgIn, IplImage* &out, int morphW,	int morphH) {

	IplImage * imgGrey;
	grayScaleImage(imgIn, imgGrey);

	int scale = SOBEL_SCALE;
	int delta = SOBEL_DELTA;
	int ddepth = SOBEL_DDEPTH;

	IplImage* grad;
	sobelAbsImage(imgGrey, grad, 1, 0, 3);

	IplImage *ImgThresh = cvCreateImage(cvGetSize(grad), IPL_DEPTH_8U, grad->nChannels);
	double Ret = cvThreshold(grad, ImgThresh, 0, 255, CV_THRESH_BINARY + CV_THRESH_OTSU);

	//Mat element = getStructuringElement(MORPH_RECT, Size(morphW, morphH));
	//morphologyEx(mat_threshold, mat_threshold, MORPH_CLOSE, element);

	IplConvKernel* kernel1 = cvCreateStructuringElementEx(morphW, morphH, int(morphW / 2), int(morphH/2), CV_SHAPE_RECT); //构建核
	IplImage *ImgEdge1 = cvCreateImage(cvGetSize(ImgThresh), IPL_DEPTH_8U, ImgThresh->nChannels);
	IplImage *ImgEdge2 = cvCreateImage(cvGetSize(ImgThresh), IPL_DEPTH_8U, ImgThresh->nChannels);
	out = cvCreateImage(cvGetSize(ImgThresh), IPL_DEPTH_8U, ImgThresh->nChannels);

	cvMorphologyEx(ImgThresh, ImgEdge1, NULL, kernel1, CV_MOP_CLOSE, 1);
	cvMorphologyEx(ImgEdge1, out, NULL, kernel1, CV_MOP_OPEN, 1);
	return 0;
}
//--------------------------------------------------------------------------------------------------------------

int mPlate_Locate::obtainPlates(const IplImage *src, vector<CvBox2D> &inRects, vector<mPlate> &outPlates)//int mPlate_Locate::obtainPlates(const IplImage *src, vector<CvBox2D> &inRects, vector<IplImage*> &outPlates)
{
	mPlate _Plate;
	IplImage* _plateImg;
	plateColor mColor;
	vector<CvBox2D>::iterator iter;
//#pragma omp parallel for
	for (iter = inRects.begin(); iter != inRects.end(); iter++)
	{
		_plateImg = new IplImage;
		_plateImg = rect2Img(src, *iter, 10, 10);
		
		if (!verifyImgColor(_plateImg, mColor)) continue;
		if (!verifyImgWaves(_plateImg, mColor)) continue;

		//_Plate = new mPlate;

		//cvShowImage("pic", _plateImg);
		//cvWaitKey();

		DrawBox(locateImg, *iter,CV_RGB(255,0,0));//draw rect to

		_Plate.setPlateImg(_plateImg);
		_Plate.setPlateColor(mColor);
		outPlates.push_back(_Plate);
		
		//outPlates.push_back(_plateImg);
	}
	return 0;
}

//----------------------------------------------------------------------------------------------------------------
vector<CvBox2D> mPlate_Locate::getImageRect(IplImage* ImageEdge)
{
	CvSeq *pContour = NULL;
	CvSeq *pConInner = NULL;//inner contour
	CvMemStorage *pStorage = NULL;
	std::vector<CvBox2D> PlateRects;
	CvBox2D rect;
	// 查找所有轮廓 find all contours
	pStorage = cvCreateMemStorage(0);
	cvFindContours(ImageEdge, pStorage, &pContour, sizeof(CvContour), CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);

	for (; pContour != NULL; pContour = pContour->h_next)
	{
		if (!verifyArea(pContour))//面积太小的区域不保存 area too small
			continue;
		rect = cvMinAreaRect2(pContour);
		if (!verifyW_div_H(rect))//矩形长宽比 rect w/h
			continue;
		PlateRects.push_back(rect);
	}
	cvReleaseMemStorage(&pStorage);
	pStorage = NULL;
	return PlateRects;
}

bool mPlate_Locate::verifyArea(CvSeq * contour)
{
	double _minArea = 600;
	double _AreaContour = fabs(cvContourArea(contour));
	if (_AreaContour > _minArea)
		return TRUE;
	else
		return FALSE;
}

bool mPlate_Locate::verifyW_div_H(CvBox2D &rectsIN)
{
	//根据长宽比排除非车牌区域-
	double W_Div_H = double(rectsIN.size.width) / double(rectsIN.size.height);
	if (W_Div_H < 1)  W_Div_H = 1./ W_Div_H;

	if (W_Div_H < 1.5 || W_Div_H > 6)
		return FALSE;
	else
		return TRUE;
}

bool mPlate_Locate::verifyImgColor(IplImage* &PlateImg, plateColor & mColor)
{
	
	int NGreen, NYellow, NBlue, NWhite, NBlack;
	NGreen = NYellow = NBlue = NWhite = NBlack = 0;
	int PlateImgCount;

	IplImage* PlateImgHSV;
	int H, S, V;
	std::vector<plateColor> COLORS;
	plateColor Color;
	CvRect Prect;
	CvMat* tempImgN = new CvMat;
	IplImage *PlateImgN;

	PlateImgHSV = cvCreateImage(cvGetSize(PlateImg), IPL_DEPTH_8U, 3);
	cvCvtColor(PlateImg, PlateImgHSV, CV_BGR2HSV);//

	if (PlateImgHSV == NULL) return FALSE;

	PlateImgCount = (PlateImgHSV->height*PlateImgHSV->width);//像素总数
	for (int row = 0; row < PlateImgHSV->height; row++)//统计颜色信息
	{
		for (int col = 0; col < PlateImgHSV->width; col++)
		{
			//获取色度，饱和度，明度。
			H =int( CV_IMAGE_ELEM(PlateImgHSV, uchar, row, col * PlateImgHSV->nChannels + 0));
			S = int(CV_IMAGE_ELEM(PlateImgHSV, uchar, row, col * PlateImgHSV->nChannels + 1));
			V = int(CV_IMAGE_ELEM(PlateImgHSV, uchar, row, col * PlateImgHSV->nChannels + 2));
			//(((elemtype*)((image)->imageData + (image)->widthStep*(row)))[(col)])
			if (11 < H && H<= 34 && S > 34)
				NYellow += 1;
			else if (35 < H && H <= 99 && S > 34)
				NGreen += 1;
			else if (99 < H && H <= 140 && S > 34)
				NBlue += 1;

			if (0 < H && H < 180 && 0 < S && S< 255 && 0 < V && V < 46)
				NBlack += 1;
			else if (0 < H && H < 180 && 0 < S && S < 43 && 221 < V && V < 225)
				NWhite += 1;
		}
	}
	float ratio = 0.6;
	if (NYellow >= int(PlateImgCount*ratio))
		Color = plateYellow;
	else if (NBlue >= int(PlateImgCount*ratio))
		Color = plateBlue;
	else if (NGreen >= int(PlateImgCount*ratio))
		Color = plateGreen;
	else if (NWhite >= int(PlateImgCount*ratio))
		Color = plateWhite;
	else if (NBlack >= int(PlateImgCount*ratio))
		Color = plateBlack;
	else
	{
		Color = plateEmpty;
		return FALSE;
	}
	mColor = Color;
	//if (Color.pColor == Empty) return FALSE;

	Bound NewBound = AccuratePlateLocation(PlateImgHSV, Color);

	if (NewBound.xLeft == NewBound.xRight || NewBound.yHeight == NewBound.yLow) return TRUE;
	PlateImgN = cvCreateImage(cvGetSize(PlateImg), IPL_DEPTH_8U, PlateImg->nChannels);
	if (Color.pColor != Green || NewBound.yLow < int((NewBound.yHeight - NewBound.yLow) / 4))//非绿色
	{
		Prect.x = NewBound.xLeft;
		Prect.y = NewBound.yLow;
		Prect.width = NewBound.xRight - NewBound.xLeft;
		Prect.height = NewBound.yHeight - NewBound.yLow;

		cvGetSubRect(PlateImg, tempImgN, Prect);
		cvGetImage(tempImgN, PlateImgN);
	}
	else
	{
		Prect.x = NewBound.xLeft;
		Prect.y = NewBound.yHeight;
		Prect.width = NewBound.xRight - NewBound.xLeft;
		Prect.height = NewBound.yHeight - int(NewBound.yLow - (NewBound.yHeight - NewBound.yLow) / 4);

		cvGetSubRect(PlateImg, tempImgN, Prect);
		cvGetImage(tempImgN, PlateImgN);
	}

	PlateImg = PlateImgN;
	return TRUE;
}

Bound mPlate_Locate::AccuratePlateLocation(IplImage* PlateImgHSV, plateColor color)
{
	Bound outB;
	int count;
	uchar H, S, V;

	outB.xLeft = PlateImgHSV->width;
	outB.xRight = 0;
	outB.yHeight = 0;
	outB.yLow = PlateImgHSV->height;


	int RowNumLimit = 21;
	int ColNumLimit;
	if (color.pColor != 3)
		ColNumLimit = int(10. * 0.8);
	else
		ColNumLimit = int(PlateImgHSV->width *0.5); //绿色有渐变 

	for (int row = 0; row < PlateImgHSV->height; row++)
	{
		count = 0;
		for (int col = 0; col < PlateImgHSV->width; col++)
		{
			H = CV_IMAGE_ELEM(PlateImgHSV, uchar, row, col * PlateImgHSV->nChannels + 0);
			S = CV_IMAGE_ELEM(PlateImgHSV, uchar, row, col * PlateImgHSV->nChannels + 1);
			V = CV_IMAGE_ELEM(PlateImgHSV, uchar, row, col * PlateImgHSV->nChannels + 2);
			if (color.Limit1 < H <= color.Limit2 && 34 < S && 46 < V)
				count += 1;
		}
		if (count > ColNumLimit)
		{
			if (outB.yLow > row)
				outB.yLow = row;
			if (outB.yHeight < row)
				outB.yHeight = row;
		}
	}
	for (int col = 0; col < PlateImgHSV->width; col++)
	{
		count = 0;
		for (int row = 0; row < PlateImgHSV->height; row++)
		{
			H = CV_IMAGE_ELEM(PlateImgHSV, uchar, row, col * PlateImgHSV->nChannels + 0);
			S = CV_IMAGE_ELEM(PlateImgHSV, uchar, row, col * PlateImgHSV->nChannels + 1);
			V = CV_IMAGE_ELEM(PlateImgHSV, uchar, row, col * PlateImgHSV->nChannels + 2);
			if (color.Limit1 < H <= color.Limit2 && 34 < S && 46 < V)
				count += 1;
		}
		if (count > (PlateImgHSV->height - RowNumLimit))
		{
			if (outB.xLeft > col)
				outB.xLeft = col;
			if (outB.xRight < col)
				outB.xRight = col;
		}
	}
	if (outB.yHeight == 0)
	{
		outB.yLow = 0;
		outB.yHeight = PlateImgHSV->height;
	}
	if (outB.xRight == 0)
	{
		outB.xLeft = 0;
		outB.xRight = PlateImgHSV->width;
	}

	return outB;
}

bool mPlate_Locate::verifyImgWaves(const IplImage* PlateImg, plateColor &Color)
{
	IplImage* imgGray;
	int wavePeak;
	grayScaleImage(PlateImg, imgGray);

	if (Color.pColor == Green || Color.pColor == Green || Color.pColor == White)
		antiImgColor(imgGray, imgGray);

	vector<mPoint> wave_peaksH, wave_peaksV;

	getWavePeak(imgGray, wavePeak, wave_peaksH, hoshorizon);
	if (wavePeak == 0)
		return FALSE;
	getWavePeak(imgGray, wavePeak, wave_peaksV, vertical);
	if (wavePeak <= 6)
		return FALSE;
	
	return TRUE;
}
