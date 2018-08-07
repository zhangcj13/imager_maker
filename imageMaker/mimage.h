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
	//opencvͼ
	IplImage *currentImage;
	IplImage *currentImageTemp;
	char *cvPath;
	
	//���ļ�
	int openImageFile(const QString &caption, const QString &dir, const QString &filer);

	//�ر�
	int closeImageFile(void);
	//����
	int saveImageFile(void);
	//���Ϊ
	int saveAsImageFile(void);
	//���α任�����ţ���ת����б
	int	resizeImgage(double seedx, double seedy);
	int	rotateImgage(double angle);
	int skewImage(double degreex, double degreey);
	int mirrorImage(int flag);
	int perspectiveImage(void);
	//�ҶȻ�ͼ��
	int grayScaleImage(void);
	//�˲��任
	int gaussianBlurImage(int blur);
	/*
	//ɾ��
	int delImageFile(void);

	//�����ļ�
	int last(void);
	int next(void);

	//�ı�
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
	//��ʼ��
	void initImageResource(void);

	//���ļ�
	

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






