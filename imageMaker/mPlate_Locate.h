
#ifndef MPLATELOCATE_H_
#define MPLATELOCATE_H_

#include "mPlate.h"

class mPlate_Locate
{
public:
	IplImage* initialImg;
	IplImage* locateImg;
	vector<mPlate> candPlates;
public:
	mPlate_Locate();
	~mPlate_Locate();
	void InitialData(IplImage *inImg);

	int LocatePlate();

public:
	int plateLocateBYColor(IplImage *src, vector<mPlate> &candPlates, int index);

	int colorSearch(const IplImage *src, const Colors r, IplImage* & out, vector<CvBox2D>  &outRects);

	int plateLocateBYSobel(IplImage* src, vector<mPlate> &candPlates, int index);

	int sobelRectSearch(const IplImage* src, vector<CvBox2D > &outRects);

	int sobelOper(const IplImage* imgIn, IplImage* &out, int morphW, int morphH);

protected:
	int obtainPlates(const IplImage *src, vector<CvBox2D> &inRects, vector<mPlate> &outPlates);
	std::vector<CvBox2D> getImageRect(IplImage* ImageEdge);

	Bound AccuratePlateLocation(IplImage* PlateImgHSV, plateColor color);
	bool verifyImgColor(IplImage* &PlateImg,plateColor & mColor);
	
	bool verifyArea(CvSeq * contour);
	bool verifyW_div_H(CvBox2D &rectsIN);

	bool verifyImgWaves(const IplImage* PlateImg, plateColor &Color);
//后期工作+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	bool verifyPlateBySVM(const IplImage* PlateImg){ return true; }
};

#endif