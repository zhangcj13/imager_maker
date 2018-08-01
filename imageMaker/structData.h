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

#endif // STRUCTDATA_H
