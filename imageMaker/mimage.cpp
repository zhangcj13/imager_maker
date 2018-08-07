#include "mimage.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QImageReader>
#include <qguiapplication.h>


mImage::mImage(QWidget *parent)
	: QWidget(parent)
{
	this->parent = parent;
	initImageResource();
}
mImage::mImage(QWidget *parent, QString &caption, QString &dir, QString &filer)
{
	this->parent = parent;
	initImageResource();
	loadImageResource(caption, dir, filer);
}

mImage::~mImage()
{
	this->parent = NULL;
}

//文件打开关闭操作
int mImage::openImageFile(const QString &caption, const QString &dir, const QString &filer)
{
	initImageResource();
	return loadImageResource(caption, dir, filer);
}

int mImage::closeImageFile(void)
{
	initImageResource();
	return 0;
}

int mImage::saveImageFile(void)
{
	pixmap.save(filename);
	return 0;
}

int mImage::saveAsImageFile(void)
{
	QString saveName = QFileDialog::getSaveFileName(this, tr("Save Image"), "", tr("Images (*.png *.bmp *.jpg)")); //选择路径
	QScreen *screen = QGuiApplication::primaryScreen();
	pixmap.save(saveName);
	return 0;
}

//私有函数----------------------------------------------------------------------------------------------：
//初始化
void mImage::initImageResource(void)
{
	index = -1;
	angle = 0;
	size = QSize(0, 0);

	filename.clear();
	path.clear();
}

//打开文件
int mImage::loadImageResource(void)
{
	//默认地址文件名字
	filename = QFileDialog::getOpenFileName(this, tr("Select image:"),
		"C:\\Users\\zhang\\Pictures", tr("Images (*.jpg *.jpeg *.png *.bmp *.gif)"));
	if (filename.isEmpty()) {
		return -1;
	}
	QByteArray temp = filename.toLocal8Bit();
	cvPath = temp.data();
	//获取图片信息，图片数据
	getFileInfoList();

	//导入数据
	upgradeFileInfo(filename, angle, 10);

	return 0;
}
int mImage::loadImageResource(const QString &caption, const QString &directory, const QString &filer)
{
	filename = QFileDialog::getOpenFileName(this, caption, directory, filer);
	if (filename.isEmpty()) {
		return -1;
	}
	QByteArray temp = filename.toLocal8Bit();
	cvPath = temp.data();
	// get file list 
	getFileInfoList();

	// load file info 
	upgradeFileInfo(filename, angle, 10);

	return 0;
}
int mImage::loadImageResource(IplImage* img)
{
	//导入数据
	upgradeFileInfo(img, angle, 10);
	return 0;
}

//get file info list from current path
int mImage::getFileInfoList(void)
{
	QFileInfo info;
	QFileInfoList infoList;
	
	path = QFileInfo(filename).absolutePath();
	dir = QFileInfo(filename).absoluteDir();


	// clear list 
	fileInfoList.clear();

	infoList = dir.entryInfoList(QDir::Files);
	for (int i = 0; i < infoList.count(); i++) {
		info = infoList.at(i);
		QString suffix = info.suffix();

		if (suffix == "jpg" || suffix == "bmp" || suffix == "png"
			|| suffix == "gif" || suffix == "jpeg") {
			fileInfoList.append(info);
		}
	}

	return 0;
}
int mImage::getFileCurIndex(void)
{
	QFileInfo info;
	int j;

	if (fileInfoList.count() <= 0) {
		qDebug() << "fileInfoList is NULL!";
		return -1;
	}

	for (j = 0; j < fileInfoList.count(); j++) {
		info = fileInfoList.at(j);
		if (info.fileName() == fileInfo.fileName()) {
			break;
		}
	}

	if (j >= fileInfoList.count()) {
		qDebug() << "Not find current file!";
		return -1;
	}

	index = j;
	//qDebug() << "Current fileInfo index: " << index;

	return index;
}
int mImage::upgradeFileInfo(QString &filename, int angle, int sizeScale)
{
	QImage imgRotate;
	QMatrix matrix;
	QImage imgScaled;

	if (filename.isEmpty()) {
		return -1;
	}

	fileInfo = QFileInfo(filename);
	
	currentImage = cvLoadImage(cvPath);
	if (currentImage->nChannels==3) cvConvertImage(currentImage, currentImage, CV_CVTIMG_SWAP_RB);
	currentImageTemp = cvCreateImage(cvSize(currentImage->width, currentImage->height), currentImage->depth, currentImage->nChannels);
	cvCopy(currentImage, currentImageTemp);// 用于修改图片的存储空间
	//if (!image.load(filename)) {	return -1;}
	if (currentImage == NULL)	{
		return -1;
	}
	image = iplImg2QImg(currentImage);

	// modify angle 
	matrix.rotate(angle * 90);
	imgRotate = image.transformed(matrix);

	if (size == QSize(0, 0)) {
		size = image.size();
	}

	// modify scale 
	imgScaled = imgRotate.scaled(size.width() * sizeScale / 10,
		size.height() * sizeScale / 10,
		Qt::KeepAspectRatio);

	// upgrade pixmap 
	pixmap = QPixmap::fromImage(imgScaled);
	size = pixmap.size();

	// upgrade index 
	index = getFileCurIndex();

	return 0;
}
int mImage::upgradeFileInfo(IplImage* imgIn, int angle, int sizeScale)
{
	QImage imgRotate;
	QMatrix matrix;
	QImage imgScaled;
	
	//交换currentImage与currentImageTemp地址,如果尺寸不相等，则为currentImageTemp重新开辟一个新的存储空间
	if (currentImage->width == imgIn->width && currentImage->height == imgIn->height
		&&currentImage->depth == imgIn->depth&&currentImage->nChannels == imgIn->nChannels)
	{
		currentImageTemp = currentImage;
		currentImage = imgIn;
	}
	else
	{
		currentImage = cvCreateImage(cvSize(imgIn->width, imgIn->height), imgIn->depth, imgIn->nChannels);
		currentImage = imgIn;
		currentImageTemp = cvCreateImage(cvSize(currentImage->width, currentImage->height), currentImage->depth, currentImage->nChannels);
		cvCopy(currentImage, currentImageTemp);// 用于修改图片的存储空间
	}
	
	image = iplImg2QImg(imgIn);

	// modify angle 
	matrix.rotate(angle * 90);
	imgRotate = image.transformed(matrix);

	size = image.size();

	// modify scale 
	imgScaled = imgRotate.scaled(size.width() * sizeScale / 10,
		size.height() * sizeScale / 10,
		Qt::KeepAspectRatio);

	// upgrade pixmap 
	pixmap = QPixmap::fromImage(imgScaled);
	size = pixmap.size();

	// upgrade index 
	index = getFileCurIndex();

	return 0;
}

//将opencv格式图片转换为Qimage
QImage mImage::iplImg2QImg(IplImage *iplImg)
{
	int nChannel = iplImg->nChannels;
	if (nChannel == 3)
	{
		QImage img;
		//cvConvertImage(iplImg, iplImg, CV_CVTIMG_SWAP_RB);
		img = QImage((const unsigned char*)iplImg->imageData, iplImg->width, iplImg->height, QImage::Format_RGB888);
		return img;
	}
	else if (nChannel == 4 )//|| nChannel == 1)
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
//
int mImage::grayScaleImage(void)
{
	
	IplImage* currentImgGrayScale = cvCreateImage(cvSize(size.width(), size.height()), IPL_DEPTH_8U, 1);
	cvCvtColor(currentImage, currentImgGrayScale, CV_BGR2GRAY);
	//cvCvtColor(currentImage, currentImgGrayScale, CV_BGR2RGB);
	loadImageResource(currentImgGrayScale);

	return 1;
}
//几何变换，缩放，旋转，倾斜
int	mImage::resizeImgage(double seedx, double seedy)
	{
		CvSize size;
		size.height = int(currentImage->height * seedx);
		size.width = int(currentImage->width * seedy);
		//IplImage* currentImageResized = cvCreateImage(size, currentImage->depth, currentImage->nChannels);
		cvCvtColor(currentImage, currentImage, CV_BGR2RGB);
		IplImage* currentImageResized = cvCreateImage(size, IPL_DEPTH_8U, currentImage->nChannels);
		cvResize(currentImage, currentImageResized, CV_INTER_LINEAR);
		loadImageResource(currentImageResized);
		return 1;
	}
int	mImage::rotateImgage(double degree)
{
	double angle = degree  * CV_PI / 180.; 
	double a = sin(angle), b = cos(angle); 
	int w_src = currentImage->width;
	int h_src = currentImage->height;
	//输出图像尺寸
	int w_dst = int(h_src * fabs(a) + w_src * fabs(b));
	int h_dst = int(w_src * fabs(a) + h_src * fabs(b));
	double map[6];
	CvMat map_matrix = cvMat(2, 3, CV_64FC1, map);
	cv2DRotationMatrix(cvPoint2D32f(w_src / 2, h_src / 2), degree, 1.0, &map_matrix);
	map[2] += (w_dst - w_src) / 2;
	map[5] += (h_dst - h_src) / 2;

	IplImage *currentImageRotated = cvCreateImage(cvSize(w_dst, h_dst), IPL_DEPTH_8U, currentImage->nChannels);

	cvWarpAffine(currentImage, currentImageRotated, &map_matrix, CV_INTER_LINEAR | CV_WARP_FILL_OUTLIERS, cvScalarAll(0));	
	loadImageResource(currentImageRotated);
	return 1;
}
int mImage::skewImage(double degreex, double degreey)
{
	double anglex = degreex  * CV_PI / 180., angley = degreey  * CV_PI / 180.;
	double ax = 1. / tan(anglex), ay = 1. / tan(angley);
	int w_src = currentImage->width;
	int h_src = currentImage->height;
	//输出图像尺寸
	int w_dst = int(w_src + h_src*cos(anglex));
	int h_dst = int(h_src + w_src*cos(angley));

	double map[6] = { 1, ax, 0, ay, 1, 1 };
	CvMat map_matrix = cvMat(2, 3, CV_64FC1, map);
	

	IplImage *currentImageRotated = cvCreateImage(cvSize(w_dst, h_dst), IPL_DEPTH_8U, currentImage->nChannels);

	cvWarpAffine(currentImage, currentImageRotated, &map_matrix, CV_INTER_LINEAR | CV_WARP_FILL_OUTLIERS, cvScalarAll(0));
	loadImageResource(currentImageRotated);
	return 1;
}
int mImage::mirrorImage(int flag)
{
	double map[6] = { -1, 0, 0, 0, -1, 0 };
	switch (flag)
	{
	case 0:
	{
		map[2] = currentImage->width;
		map[4] = 1;
		break;
	}
	case 1:
	{
		map[0] = 1;
		map[5] = currentImage->height;
		break;
	}
	case 2:
	{
		map[5] = currentImage->height;
		map[2] = currentImage->width;
		break;
	}
	}
	CvMat map_matrix= cvMat(2, 3, CV_64FC1, map);

	IplImage *currentImageMirror= cvCreateImage(cvSize(currentImage->width,currentImage->height), IPL_DEPTH_8U, currentImage->nChannels);

	cvWarpAffine(currentImage, currentImageMirror, &map_matrix, CV_INTER_LINEAR | CV_WARP_FILL_OUTLIERS, cvScalarAll(0));
	loadImageResource(currentImageMirror);
	return 1;
}
int mImage::perspectiveImage(void)
{
	
	int w_src = currentImage->width;
	int h_src = currentImage->height;

	CvPoint2D32f srcTri[4], dstTri[4]; //二维坐标下的点，类型为浮点
	CvMat* warp_mat = cvCreateMat(3, 3, CV_32FC1);

	//计算矩阵仿射变换
	srcTri[0].x = 0;
	srcTri[0].y = 0;
	srcTri[1].x = w_src - 1;  //缩小一个像素
	srcTri[1].y = 0;
	srcTri[2].x = 0;
	srcTri[2].y = h_src - 1;
	srcTri[3].x = w_src - 1;  //bot right
	srcTri[3].y = h_src - 1;
	//改变目标图像大小
	dstTri[0].x = w_src * 0.05;
	dstTri[0].y = h_src * 0.33;
	dstTri[1].x = w_src * 0.9;
	dstTri[1].y = h_src * 0.25;
	dstTri[2].x = w_src * 0.2;
	dstTri[2].y = h_src * 0.7;
	dstTri[3].x = w_src * 0.8;
	dstTri[3].y = h_src* 0.9;
	cvGetPerspectiveTransform(srcTri, dstTri, warp_mat);  //由三对点计算仿射变换 

	IplImage *currentImagePerspectived = cvCreateImage(cvSize(w_src, h_src), IPL_DEPTH_8U, currentImage->nChannels);
	cvWarpPerspective(currentImage, currentImagePerspectived, warp_mat);  //对图像做仿射变换
	loadImageResource(currentImagePerspectived);
	return 1;
}
//滤波变换
int mImage::gaussianBlurImage(int blur)
{
	IplImage* currentImgGaussianBlur = cvCreateImage(cvSize(currentImage->width, currentImage->height), IPL_DEPTH_8U, currentImage->nChannels);;
	cvSmooth(currentImage, currentImgGaussianBlur, CV_GAUSSIAN,blur, 0,0,0);
	loadImageResource(currentImgGaussianBlur);
	return 1;
}