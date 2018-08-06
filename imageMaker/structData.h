#ifndef STRUCTDATA_H
#define STRUCTDATA_H

// Qt header files
#include <QtGui>
#include <opencv2/objdetect/objdetect.hpp>

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

#endif // STRUCTDATA_H
