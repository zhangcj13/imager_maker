#ifndef STRUCTPLATE_H
#define STRUCTPLATE_H

// Qt header files
#include <QtGui>
#include <opencv2/objdetect/objdetect.hpp>

// ProcessingSettings structure definition
enum axis{ hoshorizon, vertical };
struct mPoint
{ 
	int x; 
	int y; 

	mPoint& operator=(mPoint& value)
	{
		x = value.x;
		y = value.y;
		return *this;
	}
	mPoint& operator=(const mPoint& value)
	{
		x = value.x;
		y = value.y;
		return *this;
	}
	bool operator==(mPoint& value)
	{
		return (x == value.x && y == value.y);
	}

	bool operator!=(mPoint& value)
	{
		return (x != value.x || y != value.y);
	}

};
enum Colors
{
	Empty, Yellow = 1, Blue, Green, White, Black
};
enum LocateType
{
	SOBEL, COLOR, CMSER, OTHER
};
struct showColor
{
	uchar R;
	uchar G;
	uchar B;
};

struct plateColor
{
	Colors pColor;
	uchar Limit1;
	uchar Limit2;
	showColor sColor;
};
struct Bound
{
	int xLeft;
	int xRight;
	int yHeight;
	int yLow;
};

extern const plateColor plateBlue;
extern const plateColor plateYellow;
extern const plateColor plateGreen;
extern const plateColor plateWhite;
extern const plateColor plateBlack;
extern const plateColor plateEmpty;

#define MAX_WIDTH 1000
#define GAUSSIANBLUR_SIZE 3

 const int DEFAULT_GAUSSIANBLUR_SIZE = 5;
 const int SOBEL_SCALE = 1;
 const int SOBEL_DELTA = 0;
 const int SOBEL_DDEPTH = CV_16S;
 const int SOBEL_X_WEIGHT = 1;
 const int SOBEL_Y_WEIGHT = 0;
 const int DEFAULT_MORPH_SIZE_WIDTH = 17;  // 17
 const int DEFAULT_MORPH_SIZE_HEIGHT = 3;  // 3


// Display the image.
#define SHOW_IMAGE(imgName, debug) \
  if (debug) { \
    namedWindow("imgName", WINDOW_AUTOSIZE); \
    moveWindow("imgName", 500, 500); \
    imshow("imgName", imgName); \
    waitKey(0); \
    destroyWindow("imgName"); \
    }

 struct mCategory
 {
	 int size;
	 std::string cCategory;
	 mCategory(int _size, std::string _Category)
	 {
		 size = _size;
		 cCategory = _Category;
	 }
 };
/* std::string categoryChars2[34] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"
	 , "A", "B", "C", "D", "E", "F", "G", "H", "J", "K", "L", "M", "N", "P", "Q", "R", "S"
	 , "T", "U", "V", "W", "X", "Y", "Z" };*/


#endif // STRUCTPLATE_H