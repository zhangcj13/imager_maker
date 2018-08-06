#include "IMGMAKER_FUNC.h"

namespace imgmaker
{
	mPoint init_mPoint(int x, int y){ mPoint temp; temp.x = x; temp.y = y; return temp; }

	IplImage* colorMatch(const IplImage *src, IplImage &match, const Colors r,const bool adaptive_minsv) 
	{
		if (src->nChannels != 3)
			return NULL;

		// min value of s and v is adaptive to h
		const float max_sv = 255;
		const float minref_sv = 64;
		const float minabs_sv = 95; //95;

		int min_h ;
		int max_h ;
		switch (r) {
		case Blue:
			min_h = 100;
			max_h = 140;
			break;
		case Yellow:
			min_h = 15;
			max_h = 40;
			break;
		case Green:
			min_h = 35;
			max_h = 99;
		case White:
			min_h = 0;
			max_h = 30;
			break;
		default:
			return NULL;
			break;
		}

		IplImage* src_hsv = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 3);
		// convert to HSV space
		cvCvtColor(src, src_hsv, CV_BGR2HSV);
		//Equalize Value
		IplImage *HSplit = cvCreateImage(cvGetSize(src_hsv), IPL_DEPTH_8U, 1);
		IplImage *SSplit = cvCreateImage(cvGetSize(src_hsv), IPL_DEPTH_8U, 1);
		IplImage *VSplit = cvCreateImage(cvGetSize(src_hsv), IPL_DEPTH_8U, 1);

		cvSplit(src_hsv, HSplit, SSplit, VSplit, NULL);
		cvEqualizeHist(VSplit, VSplit);
		cvMerge(HSplit, SSplit, VSplit, NULL, src_hsv);
		// match to find the color

		
		
		float diff_h = float((max_h - min_h) / 2);
		float avg_h = min_h + diff_h;

		int channels = src_hsv->nChannels;
		int nRows = src_hsv->height;
		int nCols = src_hsv->width;

		int H, S, V;
		float s_all = 0;
		float v_all = 0;
		float count = 0;
		bool colorMatched;

		uchar* mdata = (uchar *)src_hsv->imageData;
		int step = src_hsv->widthStep / sizeof(uchar);

		for (int row = 0; row < nRows; row++)
		{
			for (int col = 0; col < nCols; col++)
			{
				//获取色度，饱和度，明度。
				//H = CV_IMAGE_ELEM(src_hsv, int, row, col * channels + 0);
				//S = CV_IMAGE_ELEM(src_hsv, int, row, col * channels + 1);
				//V = CV_IMAGE_ELEM(src_hsv, int, row, col * channels + 2);
				H = int(mdata[row*step + col*channels + 0]);
				S = int(mdata[row*step + col*channels + 1]);
				V = int(mdata[row*step + col*channels + 2]);

				s_all += S;
				v_all += V;
				count++;

				colorMatched = false;

				if (H > min_h && H < max_h) {
					float Hdiff = 0;
					if (H > avg_h)
						Hdiff = H - avg_h;
					else
						Hdiff = avg_h - H;

					float Hdiff_p = float(Hdiff) / diff_h;

					float min_sv = 0;
					if (true == adaptive_minsv)
						min_sv =
						minref_sv -
						minref_sv / 2 *
						(1
						- Hdiff_p);  // inref_sv - minref_sv / 2 * (1 - Hdiff_p)
					else
						min_sv = minabs_sv;  // add

					if ((S > min_sv && S < max_sv) && (V > min_sv && V < max_sv))
						colorMatched = true;
				}

				if (colorMatched == true)
				{
					mdata[row*step + col*channels + 0] = 0;
					mdata[row*step + col*channels + 1] = 0;
					mdata[row*step + col*channels + 2] = 255;
				}
				else
				{
					mdata[row*step + col*channels + 0] = 0;
					mdata[row*step + col*channels + 1] = 0;
					mdata[row*step + col*channels + 2] = 0;
				}
			}
		}

		// get the final binary

		
		cvSplit(src_hsv, HSplit, SSplit, VSplit, NULL);
		IplImage *src_grey = cvCreateImage(cvGetSize(VSplit), IPL_DEPTH_8U, 1);
		src_grey = VSplit;

		match = *src_grey;

		return src_grey;
	}

	IplImage* rect2Img(const IplImage *src, CvBox2D  &rect, int wp, int hp)//, IplImage & dst)
	{
		double Angle;
		CvPoint2D32f points[4];
		CvPoint2D32f PointHeight, PointRight, PointLow, PointLeft;
		CvPoint2D32f NewPointRight, NewPointLeft;
		CvPoint2D32f Pts1[3], Pts2[3];
		CvMat * map_matrix = new CvMat;
		double map[6];
		*map_matrix = cvMat(2, 3, CV_64FC1, map);
		IplImage* Dst= cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, src->nChannels);
		CvRect Prect;

		IplImage* PlateImg = new IplImage;
		CvMat *recttemp = new CvMat;
		//---------------------------------------------------------
		if (rect.angle == 0 || fabs(rect.angle) == 90)
			Angle = rect.angle + 0.1;
		else
			Angle = rect.angle;
		int _width = rect.size.width;
		int _height = rect.size.height;

		rect.center = rect.center;
		rect.size = CvSize2D32f(_width + wp, _height + hp);//扩大矩形范围
		rect.angle = Angle;

		cvBoxPoints(rect, points);//将box 四角点存储与points

		PointHeight.x = 0.;
		PointHeight.y = 0.;
		PointRight.x = 0.;
		PointRight.y = 0.;
		PointLow.x = src->width;
		PointLow.y = src->height;
		PointLeft.x = src->width;
		PointLeft.y = src->height;

		//确定矩形四个角点 4 Corner Point
		for (int i = 0; i<4; i++)
		{
			if (PointLeft.x>points[i].x)
				PointLeft = points[i];
			if (PointLow.y>points[i].y)
				PointLow = points[i];
			if (PointHeight.y<points[i].y)
				PointHeight = points[i];
			if (PointRight.x<points[i].x)
				PointRight = points[i];
		}


		if (PointLeft.y <= PointRight.y)
		{
			NewPointRight.x = PointRight.x;
			NewPointRight.y = PointHeight.y;
			Pts2[0] = PointLeft, Pts2[1] = PointHeight, Pts2[2] = NewPointRight;
			Pts1[0] = PointLeft, Pts1[1] = PointHeight, Pts1[2] = PointRight;

			cvGetAffineTransform(Pts1, Pts2, map_matrix);//角度矫正矩阵

			cvWarpAffine(src, Dst, map_matrix);

			NewPointRight = PointLimit(NewPointRight);
			PointHeight = PointLimit(PointHeight);
			PointLeft = PointLimit(PointLeft);

			//Prect = (int(PointLeft.y), int(PointHeight.y), int(PointLeft.x), int(NewPointRight.x));
			Prect = initCvRect(PointLeft, NewPointRight, PointHeight, src->width, src->height, true);
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

			cvWarpAffine(src, Dst, map_matrix);

			PointRight = PointLimit(PointRight);
			PointHeight = PointLimit(PointHeight);
			NewPointLeft = PointLimit(NewPointLeft);

			//Prect = (int(PointRight.y), int(PointHeight.y), int(NewPointLeft.x), int(PointRight.x));
			Prect = initCvRect(NewPointLeft, PointRight, PointHeight, src->width, src->height, false);
			cvGetSubRect(Dst, recttemp, Prect);
			cvGetImage(recttemp, PlateImg);
		}
		return PlateImg;
	}

	CvPoint2D32f PointLimit(CvPoint2D32f point)
	{
		if (point.x < 0)
			point.x = 0;
		if (point.y< 0)
			point.y = 0;
		return point;
	}

	inline CvRect initCvRect(CvPoint2D32f pLeft, CvPoint2D32f pRight, CvPoint2D32f pHigh,int width,int height ,bool flag)
	{
		CvRect Rect;
		if (flag )
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
		if ((Rect.x + Rect.width) > width)
			Rect.width = width - Rect.x;
		if ((Rect.y + Rect.height) >height)
			Rect.height = height - Rect.y;
		if (Rect.height == 0)
			Rect.height=1;
		if (Rect.width == 0)
			Rect.width = 1;

		return Rect;
	}

	int	 resizeImgage(const IplImage *src, IplImage* &dst, double seedx, double seedy)
	{
		CvSize size;
		size.height = int(src->height * seedx);
		size.width = int(src->width * seedy);
		dst = cvCreateImage(size, IPL_DEPTH_8U, src->nChannels);
		cvResize(src, dst, CV_INTER_LINEAR);
		return 0;
	}
	
	int  gaussianBlurImage(const IplImage *src, IplImage* &dst, int blurX, int blurY)
	{
		dst = cvCreateImage(cvSize(src->width, src->height), IPL_DEPTH_8U, src->nChannels);;
		cvSmooth(src, dst, CV_GAUSSIAN, blurX, blurY, 0, 0);
		return 0;
	}

    int grayScaleImage(const IplImage *src, IplImage* &dst)
	{
		dst = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
		if (src->nChannels == 3)
			cvCvtColor(src, dst, CV_BGR2GRAY);
		else
			cvCopy(src, dst);
		return 0;
	}

	int sobelAbsImage(const IplImage *src, IplImage* &dst, int xorder, int yorder,	int aperture_size)
	{
		IplImage* grad, *grad_abs, *imgOpening;
		grad = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
		grad_abs = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
		dst = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
		imgOpening = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);

		IplConvKernel* kernel = cvCreateStructuringElementEx(20, 20, 10, 10, CV_SHAPE_RECT); //构建核
		cvMorphologyEx(src, imgOpening, NULL, kernel, CV_MOP_OPEN, 1);
		cvAddWeighted(src, 1, imgOpening, -1, 0, imgOpening);

		cvSobel(imgOpening, grad, xorder, yorder, aperture_size);
		cvConvertScaleAbs(grad, grad_abs);
		cvAddWeighted(grad_abs, 1, grad, 0, 0, dst);
		return 0;

	}

	int antiImgColor(const IplImage *src, IplImage* &dst)
	{
		CvSize src_size = cvGetSize(src);
		int channels = src->nChannels;
		dst = cvCreateImage(src_size, IPL_DEPTH_8U, channels);
		cvCopy(src, dst);

		uchar* mdata = (uchar *)dst->imageData;
		int step = src->widthStep / sizeof(uchar);
		uchar _currentData;

		for (int row = 0; row < src_size.height; row++)
		{
			for (int col = 0; col < src_size.width; col++)
			{
				for (int _nchannel = 0; _nchannel < channels; _nchannel++)
				{
					_currentData = mdata[row*step + col*channels + _nchannel];
					mdata[row*step + col*channels + _nchannel] = 255-_currentData;
				}
				
			}

		}
		return 0;
	}

	int getWavePeak(const IplImage *src, int &wavePeak, vector<mPoint> &wave_peaks, axis mAaxis,float threshdiv)
	{
		if (src->nChannels != 1)
			return 0;
		IplImage*src_threshold = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
		double ret = cvThreshold(src, src_threshold, 0, 255, CV_THRESH_OTSU + CV_THRESH_BINARY);

		//查找水平直方图波峰
		int* _histogram;
		int _lengthH=axisHistogram(src_threshold, _histogram, mAaxis);
		
		int _min = _histogram[0];
		int _average = _histogram[0];
		for (int i = 1; i < _lengthH; i++)
		{
			if (_histogram[i] < _min)
				_min = _histogram[i];
			_average += _histogram[i];
		}
		_average = int(double(_average) / double(_lengthH));
		int _threshold = int((_min + _average) / threshdiv);

		wavePeak = findWave(_histogram, _threshold, _lengthH, wave_peaks);

		return 0;
	}

	int axisHistogram(const IplImage *src, int* &Histogram, axis mAxis)
	{
		CvSize src_size = cvGetSize(src);
		//x_histogram = np.sum(PlateImgGray, axis = 1)
		uchar* mdata = (uchar *)src->imageData;
		int step = src->widthStep / sizeof(uchar);
		uchar _currentData;
		int _lengthH;

		switch (mAxis)
		{
		case hoshorizon:
		{
			_lengthH = src_size.height;
			Histogram = new int[_lengthH]{0};
			memset(Histogram, 0, _lengthH*sizeof(int));
			for (int col = 0; col < src_size.width; col++)
			{
				for (int row = 0; row < src_size.height; row++)
				{
					_currentData = mdata[row*step + col];
					Histogram[row] += int(_currentData);
				}

			}
			break;

		}
		case vertical:
		{
			_lengthH = src_size.width;
			Histogram = new int[_lengthH];
			memset(Histogram, 0, _lengthH*sizeof(int));
			for (int row = 0; row < src_size.height; row++)
			{
				for (int col = 0; col < src_size.width; col++)
				{
					_currentData = mdata[row*step + col];
					Histogram[col] += int(_currentData);
				}

			}
			break;
		}

		default:
			break;
		}

		return _lengthH;

	}

	int findWave(const int * Histogram, int &threshold, int &len, vector<mPoint> &wave_peaks)
	{
		int up_point = -1;  // 上升点
		bool is_peak = FALSE;
		if (Histogram[0] > threshold)
		{
			up_point = 0;
			is_peak = TRUE;
		}
		//vector<mPoint> wave_peaks;
		int i;
		for ( i = 0; i < len;i++)
		{
			if (is_peak&&Histogram[i] < threshold)
			{
				if (i - up_point > 2)
				{
					is_peak = FALSE;
					wave_peaks.push_back(init_mPoint(up_point,i));
				}
			}
			else if (!is_peak && Histogram[i] >= threshold)
			{
				is_peak = TRUE;
				up_point = i;
			}
		}
		if (is_peak && up_point != -1 && (i - up_point) > 4)
			wave_peaks.push_back(init_mPoint(up_point, i));

		return wave_peaks.size();
	}
	//类型转换
	QPixmap Iplimage2Qpixmap(IplImage *imgIn)
	{
		QImage imgPlate;
		QImage imgRotate;
		QMatrix matrix;
		QImage imgScaled;
		QPixmap pixOut;

		imgPlate = Iplimage2Qimage(imgIn);

		matrix.rotate(0);
		imgRotate = imgPlate.transformed(matrix);

		imgScaled = imgRotate.scaled(imgRotate.width(),
			imgRotate.height(),
			Qt::KeepAspectRatio);

		pixOut = QPixmap::fromImage(imgScaled);
		return pixOut;
	}
	//将opencv格式图片转换为Qimage
	QImage Iplimage2Qimage(IplImage *iplImg)
	{


		int nChannel = iplImg->nChannels;
		if (nChannel == 3)
		{
			QImage img;
			cvConvertImage(iplImg, iplImg, CV_CVTIMG_SWAP_RB);
			img = QImage((const unsigned char*)iplImg->imageData, iplImg->width, iplImg->height, QImage::Format_RGB888);
			return img;
		}
		else if (nChannel == 4)//|| nChannel == 1)
		{
			QImage img;
			img = QImage((const unsigned char*)iplImg->imageData, iplImg->width, iplImg->height, QImage::Format_ARGB32);
			return img;
		}
		else if (nChannel == 1)
		{
			QImage img(iplImg->width, iplImg->height, QImage::Format_RGB32);
			for (int i = 0; i < iplImg->height; i++)
			{
				for (int j = 0; j < iplImg->width; j++)
				{
					int r, g, b;
					b = (int)CV_IMAGE_ELEM(iplImg, uchar, i, j);
					g = b;
					r = b;
					img.setPixel(j, i, qRgb(r, g, b));
				}
			}
			return img;
		}
	}
	//采用cvbox2d 画出矩形
	int DrawBox(IplImage* img, CvBox2D box, CvScalar color)
	{
		CvPoint2D32f point[4];
		int i;
		for (i = 0; i<4; i++)
		{
			point[i].x = 0;
			point[i].y = 0;
		}
		cvBoxPoints(box, point); //计算二维盒子顶点 
		CvPoint pt[4];
		for (i = 0; i<4; i++)
		{
			pt[i].x = (int)point[i].x;
			pt[i].y = (int)point[i].y;
		}
		cvLine(img, pt[0], pt[1], color, 2, 8, 0);
		cvLine(img, pt[1], pt[2], color, 2, 8, 0);
		cvLine(img, pt[2], pt[3], color, 2, 8, 0);
		cvLine(img, pt[3], pt[0], color, 2, 8, 0);
		return 0;
	}
	//矩阵截取
	int cutImg(const IplImage *src, IplImage *dst, int Left, int Right, int Low, int High)
	{
		CvRect Rect;
		CvMat *recttemp = new CvMat;

		Rect.x = Left;
		Rect.y = Low;
		Rect.height = int(High - Low);
		Rect.width = int(Right - Left);

		cvGetSubRect(src, recttemp, Rect);
		cvGetImage(recttemp, dst);
		return 0;
	}

	float meanImg(const IplImage *src)
	{
		uchar* mdata = (uchar *)src->imageData;
		int step = src->widthStep / sizeof(uchar);
		int channels = src->nChannels;
		int size3d = src->nChannels*src->width*src->height;
		int num3d=0;
		
		for (int i = 0; i < size3d; i++)
		{
			num3d += int(mdata[i]);
		}
		float mean = float(num3d) / float(size3d);
		return mean;
	}
	//扩展图片尺寸；
	IplImage* expandImage(const IplImage *src, int _w, int _h, uchar _color, int _flag)
	{
		int  channels = src->nChannels;
		IplImage* dst = cvCreateImage(CvSize(_w, _h), IPL_DEPTH_8U, channels);

		uchar* mdata = (uchar *)src->imageData;
		int step = src->widthStep / sizeof(uchar);
		uchar* mdatad = (uchar *)dst->imageData;
		int stepd = dst->widthStep / sizeof(uchar);

		int w_s = src->width;
		int h_s = src->height;

		int wl = int((_w - w_s) / 2.);
		int hl = int((_h - h_s) / 2.);
		int wr = abs(wl) + w_s;
		int hh = abs(hl) + h_s;

		int r_p;
		int c_p;

		for (int row = 0; row < _h; row++)
		{
			for (int col = 0; col < _w; col++)
			{
				for (int chan = 0; chan < src->nChannels; chan++)
				{
					if (col >= wl && col < wr && row >= hl && row < hh)
						mdatad[row*stepd + col*channels + chan] = mdata[(row - hl)*step + (col - wl)*channels + chan];
					else
					{
						switch (_flag)
						{
						case 0:
							mdatad[row*stepd + col*channels + chan] = _color;
							break;
						case 1:
							r_p = modInt((row - hl) , h_s);
							c_p = modInt((col - wl) , w_s);
							mdatad[row*stepd + col*channels + chan] = mdata[(r_p)*step + (c_p)*channels + chan];
							break;
						case 2:
							if ((col < wl || col > wr) && row >= hl && row < hh)
							{
								r_p = modInt((row - hl), h_s);
								c_p = w_s - modInt((col - wl), w_s);
							}
							else if (col >= wl && col < wr && (row < hl || row > hh))
							{
								r_p = h_s-modInt((row - hl), h_s);
								c_p = modInt((col - wl), w_s);
							}
							else
							{
								r_p = h_s-modInt((row - hl), h_s);
								c_p = w_s-modInt((col - wl), w_s);
							}
							
							mdatad[row*stepd + col*channels + chan] = mdata[(r_p)*step + (c_p)*channels + chan];
							break;
						}
					}
						
				}
			}
		}
		return dst;

	}

	IplImage* resizeImgage(const IplImage *src,  int _w, int _h)
	{
		IplImage* dst = cvCreateImage(CvSize(_w,_h), IPL_DEPTH_8U, src->nChannels);
		cvResize(src, dst, CV_INTER_LINEAR);
		return dst;
	}

	IplImage* mirrorImage(const IplImage *src,int flag)
	{
		double map[6] = { -1, 0, 0, 0, -1, 0 };
		switch (flag)
		{
		case 0:
		{
			map[2] = src->width;
			map[4] = 1;
			break;
		}
		case 1:
		{
			map[0] = 1;
			map[5] = src->height;
			break;
		}
		case 2:
		{
			map[5] = src->height;
			map[2] = src->width;
			break;
		}
		}
		CvMat map_matrix = cvMat(2, 3, CV_64FC1, map);
		IplImage *currentImageMirror = cvCreateImage(cvSize(src->width, src->height), IPL_DEPTH_8U, src->nChannels);
		cvWarpAffine(src, currentImageMirror, &map_matrix, CV_INTER_LINEAR | CV_WARP_FILL_OUTLIERS, cvScalarAll(0));
		return currentImageMirror;
	}

	IplImage* rotateImgage(const IplImage*src, double degree)
	{
		double angle = degree  * CV_PI / 180.;
		double a = sin(angle), b = cos(angle);
		int w_src = src->width;
		int h_src = src->height;
		//输出图像尺寸
		int w_dst = int(h_src * fabs(a) + w_src * fabs(b));
		int h_dst = int(w_src * fabs(a) + h_src * fabs(b));
		double map[6];
		CvMat map_matrix = cvMat(2, 3, CV_64FC1, map);
		cv2DRotationMatrix(cvPoint2D32f(w_src / 2, h_src / 2), degree, 1.0, &map_matrix);
		map[2] += (w_dst - w_src) / 2;
		map[5] += (h_dst - h_src) / 2;

		IplImage *ImageRotated = cvCreateImage(cvSize(w_dst, h_dst), IPL_DEPTH_8U, src->nChannels);

		cvWarpAffine(src, ImageRotated, &map_matrix, CV_INTER_LINEAR | CV_WARP_FILL_OUTLIERS, cvScalarAll(0));

		return ImageRotated;
	}

	mMatrix<size_t> getImgHistorm(const IplImage*src,int _nDiv)
	{
		size_t channels = src->nChannels;
		mMatrix<size_t> Hist(channels, _nDiv);
		
		uchar* mdata = (uchar *)src->imageData;
		int step = src->widthStep / sizeof(uchar);

		for (int row = 0; row < src->height; row++)		{
			for (int col = 0; col < src->width; col++)			{
				for (int chan = 0; chan < channels; chan++)				{
					int temp = int(mdata[row*step + col*channels + chan]);
					Hist(chan, temp)++;
				}
			}
		}
		return Hist;
	}

	void resetHistorm(const mMatrix<size_t> hist, mMatrix<size_t> *dhist, size_t _minIN, size_t _maxIn, float _factor)
	{
		/*assert(_minOut < hist.getcols() && _maxIn >= 0);
		float ratioIn = (float)(_maxIn - _minIN) / hist.getcols();
		for (int i = 0; i < hist.getrows(); ++i){
			for (int j = 0; j < hist.getcols(); ++j){
				//int labelY = round(_Vmin + (float)j*bili*pow((float)j*bili / (_Vmax - _Vmin), 1./ _factor));
				float fLabelIn = (float)(_maxIn + (float)j*ratioIn*pow((float)j*ratioIn / (_maxIn - _maxIn), 1. / _factor));
				int iLabelIn = int(fLabelIn);
				float l2r = fLabelIn - iLabelIn;

				float fLabelOut = (float)(_maxIn + j*ratioIn);
				if (l2r != 0)
				{
					(*dhist)(i, iLabelIn) += (size_t)hist(i, j)*(1 - l2r);
					(*dhist)(i, iLabelIn + 1) += (size_t)hist(i, j)*l2r;
				}
				else
					(*dhist)(i, iLabelIn) += hist(i, j);
			}
		}
		for (int i = 0; i < hist.getrows(); ++i){
			for (int j = _minOut; j < _minOut; ++j){
			}
		}*/
	}

	bool getColorLevelTable(PColorLevelItem item, mMatrix<uchar> *clTable)
	{
		size_t diff = (size_t)(item.Highlight - item.Shadow);
		size_t outDiff = (size_t)(item.OutHighlight - item.OutShadow);

		assert(item.Highlight < 256 && item.OutShadow<256 && item.Midtones>=0.1 && item.Midtones<9.99);

		float coef = 255.0 / diff;
		float outCoef = outDiff / 255.0;
		float exponent = 1.0 / item.Midtones;

		for (int i = 0; i < 256; i++){
			int v;
			if ((*clTable)(i)<= (uchar)item.Shadow)
				v = 0;
			else{
				v = (int)(((*clTable)(i)-item.Shadow) * coef + 0.5);
				if (v > 255)
					v = 255;
			}
			v = (int)(pow(v / 255.0, exponent) * 255.0 + 0.5);
			(*clTable)(i) = (unsigned char)(v * outCoef + item.OutShadow + 0.5);
		}
		return true;
	}

	int imageColorLevel(const IplImage* src, IplImage* dst, PColorLevelItem item,int charchaneel)
	{
		//色阶表替换法替换三个通道的数据
		mMatrix<uchar> ctable(1,256);
		ctable.setEqualRatioM();
		getColorLevelTable(item, &ctable);

		int channels = src->nChannels;
		if (channels == 1) charchaneel = 0;

		uchar* mdata = (uchar *)src->imageData;
		int step = src->widthStep / sizeof(uchar);

		uchar* mdataD = (uchar *)dst->imageData;
		int stepD = dst->widthStep / sizeof(uchar);

		for (int row = 0; row < src->height; row++)
		{
			for (int col = 0; col < src->width; col++)
			{
				switch (item.numchannel){
				case 0:{
					mdataD[row*stepD + col*channels] = ctable(int(mdata[row*step + col*channels]));
					break;
				}
				case 1:{
					mdataD[row*stepD + col*channels+1] = ctable(int(mdata[row*step + col*channels+1]));
					break;
				}
				case 2:{
					mdataD[row*stepD + col*channels+2] = ctable(int(mdata[row*step + col*channels+2]));
					break;
				}
				case 3:{
					mdataD[row*stepD + col*channels] = ctable(int(mdata[row*step + col*channels]));
					mdataD[row*stepD + col*channels+1] = ctable(int(mdata[row*step + col*channels+1]));
					mdataD[row*stepD + col*channels+2] = ctable(int(mdata[row*step + col*channels+2]));
					break;
				}
				}
			}
		}
		return 0;

	}
}