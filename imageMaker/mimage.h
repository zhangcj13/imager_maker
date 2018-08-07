#ifndef MIMAGE_H
#define MIMAGE_H

#include <QWidget>
#include <QImage>
#include <QPixmap>
#include <QDir>
#include <QSize>
#include <QFileInfo>
#include <QFileInfoList>

#include <vector>


#include "mOpenCV.h"

class mImage : public QWidget
{
	Q_OBJECT
public:
	explicit mImage(QWidget *parent = 0);
	explicit mImage(QWidget *parent, QString &caption, QString &dir, QString &filer);
	~mImage();
public:
	QWidget *parent;

	int index;
	int angle;
	QSize size;
	QString filename;
	QString path;
	QDir dir;
	QFileInfo fileInfo;
	QFileInfoList fileInfoList;
	
	QImage image;
	QPixmap pixmap;
	std::vector<QPixmap> history;
	//opencv图
	IplImage *currentImage;
	IplImage *currentImageTemp;
	char *cvPath;
	
	//打开文件
	int openImageFile(const QString &caption, const QString &dir, const QString &filer);

	//关闭
	int closeImageFile(void);
	//保存
	int saveImageFile(void);
	//另存为
	int saveAsImageFile(void);
	//几何变换，缩放，旋转，倾斜
	int	resizeImgage(double seedx, double seedy);
	int	rotateImgage(double angle);
	int skewImage(double degreex, double degreey);
	int mirrorImage(int flag);
	int perspectiveImage(void);
	//灰度化图像
	int grayScaleImage(void);
	//滤波变换
	int gaussianBlurImage(int blur);
	/*
	//删除
	int delImageFile(void);

	//上下文件
	int last(void);
	int next(void);

	//改变
	int zoomIn(void);
	int zoomOut(void);
	int spinToRight(void);
	int spinToLeft(void);
	*/
public:
	int loadImageResource(void);
	int loadImageResource(const QString &caption, const QString &dir, const QString &filer);
	int loadImageResource(IplImage* img);
protected:
	//初始化
	void initImageResource(void);

	//打开文件
	

	//get file info list from current path
	int getFileInfoList(void);
	int getFileCurIndex(void);
	int upgradeFileInfo(QString &filename, int angle, int sizeScale);
	int upgradeFileInfo(IplImage* img, int angle, int sizeScale);
	QImage iplImg2QImg(IplImage *cvimage);

signals:

public slots :
};
#endif // MIMAGE_H






