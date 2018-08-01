#include "PlatePredict.h"


PlatePredict::PlatePredict()
{
	this->parent = parent;
	initImageResource();
}

PlatePredict::~PlatePredict()
{
}

void PlatePredict::LoadImage(IplImage *inImg)
{
	loadImageResource(inImg);
	int w_src = currentImage->width;
	MaxWidth = 1000;
	MinArea = 1000.;
	if (w_src> MaxWidth)
	{
		double ResizeRate = double(MaxWidth )/double( w_src);
		resizeImgage(ResizeRate, ResizeRate);
	}
	
	gaussianBlurImage(3);
	imgGray = cvCreateImage(cvSize(currentImage->width, currentImage->height), IPL_DEPTH_8U, 1);
	cvCvtColor(currentImage, imgGray, CV_BGR2GRAY);
}

void PlatePredict::FindPlateLocation(void)
{ 	
	//cvContourArea(contourStorage);
	//cvClearMemStorage(contourStorage);//清空存储

    IplImage *ImgEdge=getImageEdge(imgGray);

	std::vector<CvBox2D> PlateRects = (getImageRect(ImgEdge));
	eraseRectBaseWH(&PlateRects);

	std::vector<IplImage*> PlateImgs = getPlateImgs(&PlateRects);
	erasePlateImgBaseColor(&PlateImgs);

	//--------------------------------------------------------
	std::vector<IplImage*>::iterator iter;
	for (iter = PlateImgs.begin(); iter != PlateImgs.end(); iter++)
	{
		cvShowImage("carplate", *iter);
		cvWaitKey();
	}

	//--------------------------------------------------------

	
	
	loadImageResource(currentImage);

	//loadImageResource(ImgEdge);


}

CvPoint2D32f PlatePredict::PointLimit(CvPoint2D32f point)
{
	if (point.x < 0)
		point.x = 0;
	if (point.y< 0)
		point.y = 0;
	return point;
}

IplImage * PlatePredict::getImageEdge(IplImage *imageIn)
{
	if (imageIn->nChannels != 1)
		return NULL;

	IplImage *ImgOpening = cvCreateImage(cvSize(imageIn->width, imageIn->height), IPL_DEPTH_8U, imageIn->nChannels);

	int value[400];
	for (int i = 0; i < 400; ++i)
		value[i] = 0;
	IplConvKernel* kernel = cvCreateStructuringElementEx(20, 20, 10, 10, CV_SHAPE_RECT, value); //构建核
	cvMorphologyEx(imgGray, ImgOpening, NULL, kernel, CV_MOP_OPEN, 1);
	//cvSaveImage("C:\\Users\\zhang\\Pictures\\CPPFILE\\CPP_imgGray.jpg", imgGray);
	//cvSaveImage("C:\\Users\\zhang\\Pictures\\CPPFILE\\CPP_ImgOpening.jpg", ImgOpening);
	
	cvAddWeighted(imgGray, 1, ImgOpening, -1, 0, ImgOpening);
	//cvSaveImage("C:\\Users\\zhang\\Pictures\\CPPFILE\\CPP_addweight.jpg", ImgOpening);
	//二值化, 边界搜寻
	IplImage *ImgThresh = cvCreateImage(cvSize(ImgOpening->width, ImgOpening->height), IPL_DEPTH_8U, ImgOpening->nChannels);
	double Ret = cvThreshold(ImgOpening, ImgThresh, 0, 255, CV_THRESH_BINARY + CV_THRESH_OTSU);
	
	IplImage *ImgEdge = cvCreateImage(cvSize(ImgThresh->width, ImgThresh->height), IPL_DEPTH_8U, ImgThresh->nChannels);
	cvCanny(ImgThresh, ImgEdge, 100, 200, 3);
	
	//边界连通
	int value1[76];
	for (int i = 0; i < 76; ++i)
		value1[i] = 1;
	//IplConvKernel* kernel1 = cvCreateStructuringElementEx(4, 19, 2, 10, CV_SHAPE_CUSTOM, value1); //构建核
	IplConvKernel* kernel1 = cvCreateStructuringElementEx(19, 4, 10, 2, CV_SHAPE_RECT, value1); //构建核
	IplImage *ImgEdge1 = cvCreateImage(cvSize(ImgThresh->width, ImgThresh->height), IPL_DEPTH_8U, ImgThresh->nChannels);
	IplImage *ImgEdge2 = cvCreateImage(cvSize(ImgThresh->width, ImgThresh->height), IPL_DEPTH_8U, ImgThresh->nChannels);

	cvMorphologyEx(ImgEdge, ImgEdge1, NULL, kernel1, CV_MOP_CLOSE, 1);
	cvMorphologyEx(ImgEdge1, ImgEdge2, NULL, kernel1, CV_MOP_OPEN, 1);
	//cvSaveImage("C:\\Users\\zhang\\Pictures\\CPPFILE\\CPP_ImgEdge1.jpg", ImgEdge1);
	//cvSaveImage("C:\\Users\\zhang\\Pictures\\CPPFILE\\CPP_ImgEdge2.jpg", ImgEdge2);
	return ImgEdge2;
}

/*std::vector<CvSeq*> PlatePredict::getImageContour(IplImage* ImageEdge)
{
	//std::vector<CvSeq*> Countours;
	//查找图片整体形成的连同区域
	double dConArea;
	CvSeq *pContour = NULL;
	CvSeq *pConInner = NULL;
	CvMemStorage *pStorage = NULL;
	std::vector<CvBox2D> PlateRect;
	CvBox2D rect;

	// 查找所有轮廓-----------------------------------------------------------------------
	pStorage = cvCreateMemStorage(0);
	cvFindContours(ImageEdge, pStorage, &pContour, sizeof(CvContour), CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);

	for (; pContour != NULL; pContour = pContour->h_next)
	{
		double AreaContour = fabs(cvContourArea(pContour));
		if (AreaContour< MinArea)//面积太小的区域删除
			continue;
		rect = cvMinAreaRect2(pContour);
		PlateRect.push_back(rect);
		//Countours.push_back(pContour);
		//CvRect rect = cvBoundingRect(pContour, 0);
		//cvRectangle(currentImage, cvPoint(rect.x, rect.y), cvPoint(rect.x + rect.width, rect.y + rect.height), CV_RGB(255, 0, 0), 1, 8, 0);

	}
	cvReleaseMemStorage(&pStorage);
	pStorage = NULL;
	//return Countours;

}*/
std::vector<CvBox2D> PlatePredict::getImageRect(IplImage* ImageEdge)
{
	//查找图片整体形成的连同区域
	double dConArea;
	CvSeq *pContour = NULL;
	CvSeq *pConInner = NULL;
	CvMemStorage *pStorage = NULL;
	std::vector<CvBox2D> PlateRects;
	CvBox2D rect;
	CvRect Prect;

	// 查找所有轮廓-----------------------------------------------------------------------
	pStorage = cvCreateMemStorage(0);
	cvFindContours(ImageEdge, pStorage, &pContour, sizeof(CvContour), CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);
	
	for (; pContour != NULL; pContour = pContour->h_next)
	{
		double AreaContour = fabs(cvContourArea(pContour));
		if (AreaContour< MinArea)//面积太小的区域删除
			continue;
		rect = cvMinAreaRect2(pContour);
		PlateRects.push_back(rect);

		//Prect=cvBoundingRect(pContour);
		//cvRectangleR(this->currentImage, Prect, CV_RGB(255, 0, 0));

	}
	cvReleaseMemStorage(&pStorage);
	pStorage = NULL;
	return PlateRects;
}
void PlatePredict::eraseRectBaseWH(std::vector<CvBox2D> *rectsIN)
{
	//根据长宽比排除非车牌区域-
	std::vector<CvBox2D> PlateRects;
	std::vector<CvBox2D>::iterator iter;
	CvBox2D rect;
	double W_Div_H;//

	iter = rectsIN->begin();
	while ( iter != rectsIN->end())
	{
		W_Div_H = iter->size.width / iter->size.height;
		if (W_Div_H < 1)  W_Div_H = 1 / W_Div_H;

		if (W_Div_H < 1.5 || W_Div_H > 6)
		{
			iter = rectsIN->erase(iter);
		}
		else
		{
			iter++;
		}
		/*if (W_Div_H < 1.5 || W_Div_H < 6)
			PlateRects.push_back(*iter);
		
		iter++;*/
	}
	//return PlateRects;
}
std::vector<IplImage*> PlatePredict::getPlateImgs(std::vector<CvBox2D> *PlateRect)
{
	//角度矫正
	std::vector<IplImage*> PlateImgs; //存储角度矫正后的截取的车牌区域图片
	std::vector<CvBox2D>::iterator iter;
	CvPoint2D32f ptR[4], Pts1[3], Pts2[3];
	CvPoint2D32f PointHeight, PointRight, PointLow, PointLeft;
	CvBox2D rect;
	float Angle;

	//CvPoint2D32f PointRightL, PointRightH, PointLeftL, PointLeftH;
	CvPoint2D32f NewPointRight;
	CvPoint2D32f NewPointLeft;
	double map[6];
	CvMat * map_matrix = new CvMat;
	*map_matrix = cvMat(2, 3, CV_64FC1, map);
	IplImage* Dst = cvCreateImage(cvSize(currentImage->width, currentImage->height), IPL_DEPTH_8U, currentImage->nChannels);
	IplImage* PlateImg;
	CvMat *recttemp ;
	CvRect Prect;

	for (iter = PlateRect->begin(); iter != PlateRect->end(); iter++)
	{
		PlateImg = new IplImage;
		recttemp = new CvMat;
		//if (iter->angle>-1 && iter->angle < 1)
		if (iter->angle == 0 || fabs(iter->angle) ==90 )
			Angle = iter->angle+1;
		else
			Angle = iter->angle;

		rect.center = iter->center;
		rect.size = CvSize2D32f(iter->size.width*1.1 + 5, iter->size.height*1.1 + 5);//扩大矩形范围
		rect.angle = Angle;
		cvBoxPoints(rect, ptR);//将box 四角点存储与ptR

		PointHeight.x =0.;
		PointHeight.y = 0.;
		PointRight.x = 0.;
		PointRight.y = 0.;
		PointLow.x  = this->imgGray->width;
		PointLow.y = this->imgGray->height;
		PointLeft.x = this->imgGray->width;
		PointLeft.y = this->imgGray->height;

		//确定矩形四个角点
		for (int i = 0; i<4; i++)
		{
			if (PointLeft.x>ptR[i].x)
				PointLeft = ptR[i];
			if (PointLow.y>ptR[i].y)
				PointLow = ptR[i];
			if (PointHeight.y<ptR[i].y)
				PointHeight = ptR[i];
			if (PointRight.x<ptR[i].x)
				PointRight = ptR[i];
		}


		if (PointLeft.y <= PointRight.y)
		{
			NewPointRight.x = PointRight.x;
			NewPointRight.y = PointHeight.y;
			Pts2[0] = PointLeft, Pts2[1] = PointHeight, Pts2[2] = NewPointRight;
			Pts1[0] = PointLeft, Pts1[1] = PointHeight, Pts1[2] = PointRight;

			cvGetAffineTransform(Pts1, Pts2, map_matrix);//角度矫正矩阵

			cvWarpAffine(this->currentImage, Dst, map_matrix);

			NewPointRight = PointLimit(NewPointRight);
			PointHeight = PointLimit(PointHeight);
			PointLeft = PointLimit(PointLeft);
			//Prect = (int(PointLeft.y), int(PointHeight.y), int(PointLeft.x), int(NewPointRight.x));
			Prect = initCvRect(PointLeft, NewPointRight, PointHeight, 0);
			cvGetSubRect(Dst, recttemp, Prect);
			cvGetImage(recttemp, PlateImg);
		}
		else if (PointLeft.y>PointRight.y)
		{
			NewPointLeft.x = PointLeft.x;
			NewPointLeft.y = PointHeight.y;
			Pts2[0] = NewPointLeft, Pts2[1] = PointHeight, Pts2[2] = PointRight;
			Pts1[0] = PointLeft, Pts1[1] = PointHeight, Pts1[2] = PointRight;

			cvGetAffineTransform(Pts1, Pts2, map_matrix);

			cvWarpAffine(this->currentImage, Dst, map_matrix);

			PointRight = PointLimit(PointRight);
			PointHeight = PointLimit(PointHeight);
			NewPointLeft = PointLimit(NewPointLeft);

			//Prect = (int(PointRight.y), int(PointHeight.y), int(NewPointLeft.x), int(PointRight.x));
			Prect = initCvRect(NewPointLeft,PointRight, PointHeight, 1);
			cvGetSubRect(Dst, recttemp, Prect);
			cvGetImage(recttemp, PlateImg);
		}
		
		PlateImgs.push_back(PlateImg);
		//cvShowImage("sssssssssssssssss", PlateImg);
		//cvWaitKey();
	}
	return PlateImgs;
}
void PlatePredict::erasePlateImgBaseColor(std::vector<IplImage*> *PlateImgs)
{
	std::vector<IplImage*>::iterator iter; //存储角度矫正后的截取的车牌区域图片
	int NGreen, NYellow, NBlue, NWhite, NBlack;
	int PlateImgCount;
	IplImage* PlateImgHSV;
	uchar H, S, V;
	std::vector<plateColor> COLORS;
	plateColor Color;
	CvRect Prect;
	CvMat* tempImgN = new CvMat;
	IplImage *PlateImgN;

	iter = PlateImgs->begin();
	while (iter != PlateImgs->end())
	{
		int NGreen = NYellow = NBlue = NWhite = NBlack = 0;
		PlateImgHSV = cvCreateImage(cvSize((*iter)->width, (*iter)->height), IPL_DEPTH_8U,3);
		cvCvtColor(*iter, PlateImgHSV, CV_BGR2HSV);//
		if (PlateImgHSV == NULL)
		{
			iter++;
			continue;
		}
		PlateImgCount =(PlateImgHSV->height*PlateImgHSV->width);//像素总数
		for (int row = 0; row < PlateImgHSV->height; row++)
		{
			for (int col = 0; col < PlateImgHSV->width; col++)
			{
				//获取色度，饱和度，明度。
				H = CV_IMAGE_ELEM(PlateImgHSV, uchar, row, col * PlateImgHSV->nChannels + 0);
				S = CV_IMAGE_ELEM(PlateImgHSV, uchar, row, col * PlateImgHSV->nChannels + 1);
				V = CV_IMAGE_ELEM(PlateImgHSV, uchar, row, col * PlateImgHSV->nChannels + 2);
				//(((elemtype*)((image)->imageData + (image)->widthStep*(row)))[(col)])
				if (11 < H <= 34 && S > 34)
					NYellow += 1;
				else if (35 < H <= 99 && S > 34)
					NGreen += 1;
				else if (99 < H <= 124 && S > 34)
					NBlue += 1;

				if (0 < H < 180 && 0 < S < 255 && 0 < V < 46)
					NBlack += 1;
				else if (0 < H < 180 && 0 < S < 43 && 221 < V < 225)
					NWhite += 1;
			}
		}

		if (NYellow >= PlateImgCount*0.5)
		{
			Color.pColor = Yellow;
			Color.Limit1 = 11;
			Color.Limit2 = 34;
			Color.sColor = { 0, 255, 255 };
		}
		else if (NBlue >= PlateImgCount*0.5)
		{
			Color.pColor = Blue;
			Color.Limit1 = 100;
			Color.Limit2 = 124;
			Color.sColor = { 255, 0, 0 };
		}
		else if (NGreen >= PlateImgCount*0.5)
		{
			Color.pColor = Green;
			Color.Limit1 = 35;
			Color.Limit2 = 99;
			Color.sColor = { 0, 255, 0 };
		}
		else if (NWhite >= PlateImgCount*0.5)
		{
			Color.pColor = White;
			Color.Limit1 = 0;
			Color.Limit2 = 0;
			Color.sColor = { 255, 255, 255 };
		}

		else if (NBlack >= PlateImgCount*0.5)
		{
			Color.pColor = Black;
			Color.Limit1 = 0;
			Color.Limit2 = 0;
			Color.sColor = { 0, 0, 0 };
		}
		else
		{
			Color.pColor = Empty;
			Color.Limit1 = 0;
			Color.Limit2 = 0;
			Color.sColor = { 0, 0, 255 };
		}
		
		if (Color.pColor == 0)
		{
			iter = PlateImgs->erase(iter);
			continue;
		}
		COLORS.push_back(Color);
		Bound NewBound = AccuratePlateLocation(PlateImgHSV, Color);
		
		if (NewBound.xLeft == NewBound.xRight || NewBound.yHeight == NewBound.yLow)
		{
			iter++;
			continue;
		}
		PlateImgN = new IplImage;
		if (Color.pColor != 3 || NewBound.yLow < int((NewBound.yHeight - NewBound.yLow) / 4))//绿色
		{
			//Prect = (NewBound.yLow, NewBound.yHeight, NewBound.xLeft, NewBound.xRight);
			Prect.x = NewBound.xLeft;
			//Prect.y = NewBound.yHeight;
			Prect.y = NewBound.yLow;
			Prect.width = NewBound.xRight - NewBound.xLeft-1;
			Prect.height = NewBound.yHeight - NewBound.yLow-1;

			cvGetSubRect(*iter, tempImgN, Prect);
			cvGetImage(tempImgN, PlateImgN);
		}
		else
		{
			//Prect = (int(NewBound.yLow - (NewBound.yHeight - NewBound.yLow) / 4), NewBound.yHeight, NewBound.xLeft, NewBound.xRight);
			Prect.x = NewBound.xLeft;
			Prect.y = NewBound.yHeight;
			Prect.width = NewBound.xRight - NewBound.xLeft;
			Prect.height = NewBound.yHeight - int(NewBound.yLow - (NewBound.yHeight - NewBound.yLow) / 4);

			cvGetSubRect(*iter, tempImgN, Prect);
			cvGetImage(tempImgN, PlateImgN);
		}
		//cvShowImage("im", *iter);
		//cvWaitKey();
		*iter = PlateImgN;
		iter++;
	}
}

Bound PlatePredict::AccuratePlateLocation(IplImage* PlateImgHSV,plateColor color)
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
CvRect PlatePredict::initCvRect(CvPoint2D32f pLeft, CvPoint2D32f pRight, CvPoint2D32f pHigh, int flag)
{
	//[int(LeftPoint[1]) : int(HeightPoint[1]), int(LeftPoint[0]) : int(NewPointRight[0])]
	//[int(RightPoint[1]):int(HeightPoint[1]), int(NewLeftPoint[0]):int(RightPoint[0])]
	CvRect Rect;
	if (flag == 0)
	{
		Rect.x = int(pLeft.x);
		Rect.y = int(pLeft.y);
		Rect.height = int(pHigh.y - pLeft.y);
		Rect.width = int(pRight.x - pLeft.x);
	}
	else
	{
		Rect.x = int(pLeft.x);
		Rect.y = int(pRight.y);
		Rect.height = int(pHigh.y - pRight.y);
		Rect.width = int(pRight.x - pLeft.x);
	}
	if ((Rect.x + Rect.width) > this->imgGray->width)
		Rect.width = this->imgGray->width - Rect.x;
	if ((Rect.y + Rect.height) > this->imgGray->height)
		Rect.width = this->imgGray->height - Rect.y;

	return Rect;
}

QPixmap PlatePredict::IplImg2Qpix(IplImage *imgIn)
{
	QImage imgPlate;
	QImage imgRotate;
	QMatrix matrix;
	QImage imgScaled;
	QPixmap pixOut;

	imgPlate = iplImg2QImg(imgIn);

	matrix.rotate(0);
	imgRotate = imgPlate.transformed(matrix);

	imgScaled = imgRotate.scaled(imgRotate.width(),
		imgRotate.height(),
		Qt::KeepAspectRatio);

	pixOut = QPixmap::fromImage(imgScaled);
	return pixOut;
}
