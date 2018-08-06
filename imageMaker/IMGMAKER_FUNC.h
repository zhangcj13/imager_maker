#ifndef IMGMAKER_FUNC_H_
#define IMGMAKER_FUNC_H_

#include "mOpenCV.h"
#include <vector>
#include "structPlate.h"
#include "structData.h"
#include "mMatrix.h"
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

	IplImage* expandImage(const IplImage *src, int _w, int _h, uchar _color,int _flag=0);
	IplImage* resizeImgage(const IplImage *src, int _w, int _h);
	IplImage* mirrorImage(const IplImage *src, int flag);
	IplImage* rotateImgage(const IplImage*src, double degree);

	inline int modInt(const int  &_x, const int & _y)
	{
		if (_x >= 0)
			return _x%_y;
		else
		{
			int c = _x;
			while (c < 0)
				c += _y;
			return c%_y;
		}
	}

	mMatrix<size_t> getImgHistorm(const IplImage*src, int _nDiv=256);

	void resetHistorm(const mMatrix<size_t> hist, mMatrix<size_t> *dhist, size_t _Vmin, size_t _Vmax, float _factor = 1.);

	bool getColorLevelTable(PColorLevelItem item, mMatrix<uchar> *clTable);

	int imageColorLevel(const IplImage* src, IplImage* dst, PColorLevelItem item, int charchaneel);
}
#endif