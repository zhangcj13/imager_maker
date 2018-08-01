#ifndef IMGMAKER_FUNC_H_
#define IMGMAKER_FUNC_H_

#include "mOpenCV.h"
#include <vector>
#include "structPlate.h"
using namespace std;

namespace imgmaker
{
	
	IplImage* colorMatch(const IplImage *src, IplImage& match, const Colors r, const bool adaptive_minsv);

	IplImage* rect2Img(const IplImage *src, CvBox2D &rect, int wp = 0, int hp = 0);//, IplImage & dst);

	CvPoint2D32f PointLimit(CvPoint2D32f point);

	inline CvRect initCvRect(CvPoint2D32f pLeft, CvPoint2D32f pRight, CvPoint2D32f pHigh, int width, int height, bool flag);
	
	int	 resizeImgage(const IplImage *src, IplImage* &dst, double seedx, double seedy);

	int  gaussianBlurImage(const IplImage *src, IplImage* &dst, int blurX = 3, int blurY = 0);

	int grayScaleImage(const IplImage *src, IplImage* &dst);

	int sobelAbsImage(const IplImage *src, IplImage* &dst, int xorder, int yorder, int aperture_size);

	int antiImgColor(const IplImage *src, IplImage* &dst);

	int getWavePeak(const IplImage *src, int &wavePeak, vector<mPoint> &wave_peaks, axis mAaxis,float threshdiv=2.0);

	int axisHistogram(const IplImage *src, int* &Histogram, axis mAxis);

	int findWave(const int * Histogram, int &threshold, int &len, vector<mPoint> &wave_peaks);

	mPoint init_mPoint(int x, int y);

	QPixmap Iplimage2Qpixmap(IplImage *imgIn);
	QImage Iplimage2Qimage(IplImage *iplImg);

	int DrawBox(IplImage* img, CvBox2D box, CvScalar color);

	int cutImg(const IplImage *src, IplImage *dst, int Left, int Right, int Low, int High);

	float meanImg(const IplImage *src);

	IplImage* expandImage(const IplImage *src, size_t _w, size_t _h, uchar _color);

}
#endif