#pragma once
#include "mimage.h"

#include <vector>
#include "structPlate.h"
class PlatePredict :
	public mImage
{
public:
	int MaxWidth;
	double MinArea;
	IplImage* imgGray;

	QPixmap pixPlate;

public:
	PlatePredict();
	~PlatePredict();
public:
	void LoadImage(IplImage *inImg);
	void FindPlateLocation(void);
private:
	IplImage* getImageEdge(IplImage *imageIn);
	//std::vector<CvSeq*> getImageContour(IplImage* ImageEdge);
	std::vector<CvBox2D> getImageRect(IplImage* ImageEdge);
	void eraseRectBaseWH(std::vector<CvBox2D> *rectsIN);
	std::vector<IplImage*> getPlateImgs(std::vector<CvBox2D> *PlateRet);
	void erasePlateImgBaseColor(std::vector<IplImage*> *PlateImgs);


	CvPoint2D32f PointLimit(CvPoint2D32f point);
	Bound AccuratePlateLocation(IplImage* PlateImgHSV, plateColor color);
	CvRect initCvRect(CvPoint2D32f pLeft, CvPoint2D32f pRight, CvPoint2D32f pHigh, int flag);

	QPixmap IplImg2Qpix(IplImage *imgIn);



};

