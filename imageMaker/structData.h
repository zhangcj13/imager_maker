#ifndef STRUCTDATA_H
#define STRUCTDATA_H

// Qt header files
#include <QtGui>
#include <opencv2/objdetect/objdetect.hpp>

#define PI 3.1415926
#define SWAP(a, b, t)  do { t = a; a = b; b = t; } while(0)
#define CLIP_RANGE(value, min, max)  ( (value) > (max) ? (max) : (((value) < (min)) ? (min) : (value)) )
#define COLOR_RANGE(value)  CLIP_RANGE(value, 0, 255)

// ProcessingSettings structure definition
struct ProcessingSettings{
	int smoothType;
	int smoothParam1;
	int smoothParam2;
	double smoothParam3;
	double smoothParam4;
	int dilateNumberOfIterations;
	int erodeNumberOfIterations;
	int flipMode;
	double cannyThreshold1;
	double cannyThreshold2;
	int cannyApertureSize;
	double facedetectScale;
	QString facedetectCascadeFilename;
	QString facedetectNestedCascadeFilename;
	cv::CascadeClassifier facedetectCascadeFile;
	cv::CascadeClassifier facedetectNestedCascadeFile;
};

// ProcessingFlags structure definition
struct ProcessingFlags{
	bool grayscaleOn;
	bool smoothOn;
	bool dilateOn;
	bool erodeOn;
	bool flipOn;
	bool cannyOn;
	bool facedetectOn;
};

// TaskData structure definition
struct TaskData{
	QRect selectionBox;
	bool setROIFlag;
	bool resetROIFlag;
};

// MouseData structure definition
struct MouseData{
	QRect selectionBox;
	bool leftButtonRelease;
	bool rightButtonRelease;
};

typedef struct PColorLevelItem
{
	size_t Shadow;
	float Midtones;
	size_t Highlight;
	size_t OutShadow;
	size_t OutHighlight;
	size_t numchannel;

	PColorLevelItem(size_t _Shadow = 0, size_t _Highlight = 255, size_t _OutShadow = 0, size_t _OutHighlight = 255, float _Midtones = 1., size_t _numchannel=3)
	{
		Shadow = _Shadow;
		Midtones = _Midtones;
		Highlight = _Highlight;
		OutShadow = _OutShadow;
		OutHighlight = _OutHighlight;
		numchannel = _numchannel;
	}
};

typedef struct PBrightContrastItem
{
	float brightness;
	float contrast;
	int mode;
	
	PBrightContrastItem(float _brightness,	float _contrast,	int _mode)
	{
		brightness = _brightness;
		contrast = _contrast;
		mode = _mode;
	}
};

typedef struct PHLSItem
{
	int hue;          //色度调整值，     数据范围:  [-180, 180]
	int lightness;   //明度调整值，    数据范围:  [-100, 100]
	int saturation;   //饱和度调整值，数据范围:  [-100, 100]
	int index;

	float left_left;  //hue range left-left
	float left;       //hue range left
	float right;	  //hue range right
	float right_right;//hue range right-right

	PHLSItem(int _hue, int _lightness, int _saturation, int _index = 0)	{
		
		hue = _hue;
		saturation = _saturation;
		lightness = _lightness;
		index = _index;
		setleftright(_index);
	}
	void setleftright(int _index){
		int data[][4] = {
				{ 0, 0, 360, 360 },
				{ 315, 345, 15, 45 },
				{ 15, 45, 75, 105 },
				{ 75, 105, 135, 165 },
				{ 135, 165, 195, 225 },
				{ 195, 225, 255, 285 },
				{ 255, 285, 315, 345 }
		};
		left_left = data[_index][0];
		left = data[_index][1];
		right = data[_index][2];
		right_right = data[_index][3];
	}

};

#endif // STRUCTDATA_H
