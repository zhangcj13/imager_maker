#ifndef IMAGEMAKER_H
#define IMAGEMAKER_H

#include <QtWidgets/QMainWindow>
#include <Qmenu>
#include <Qmenubar>
#include <QToolBar>
#include <QStatusBar>
#include <QLabel>
#include <QFileInfoList>

//#include <vector>
#include <list>

#include "mimage.h"
#include "mqabout.h"

//
#include "mOpenCV.h"
//
#include "structData.h"
//
#include "resizewindow.h"
#include "rotatewindow.h"
#include "tiltwindow.h"

#include "PlatePredict.h"
#include "PlatePredictWindow.h"

class imageMaker : public QMainWindow
{
	Q_OBJECT

public:
	explicit imageMaker(QWidget *parent = 0);
	~imageMaker();

private:
	//用于摄像机输入的实时图像变换等操作
	//ProcessingFlags processingFlags;
	//用于历史记录
	int hisCount=0;
	//std::vector<mImage> hisImage;
	std::list<IplImage> hisImage;
	std::list<QPixmap> hisPixmap;
	std::list<QString> hisFileName;
	int hisMax = 6;


	QMenuBar *menuBar;
	QToolBar *toolBar;
	QWidget *centralWidget;
	QStatusBar *statusBar;
	QLabel *imageLabel;
	mQAbout aboutWidget;
	
	mImage *imageViewer;
	//标签操作
	QAction *openAction;
	QAction *closeAction;
	QAction *saveAction;
	QAction *saveAsAction;
	//
	QAction *grayScaleAction;
	//历史
	QAction *his0, *his1, *his2, *his3, *his4, *his5;
	QMenu *HistoryMenu;
private:
	void initMainWindow(void);
	void initUiComponent(void);
	void setImageMakerViewerWidget(void);
	void setWindowComponet(void);
	void initImageResource(void);
	void loadImageResource(void);

	void historyOperate(void);
	void updateHisTags(void);

public slots:

    void TestActionTriggered(void);
	void plateActionTriggered(void);



	void openActionTriggered(void);
	void closeActionTriggered(void);
	void saveActionTriggered(void);
	void saveAsActionTriggered(void);

	void aboutQtTriggered(void);
	void aboutTriggered(void);
	//
	void resizeActionTriggered();
	void rotateActionTriggered();
	void tiltActionTriggered();
	void HMirrortActionTriggered(void);
	void VMirrortActionTriggered(void);
	void MirrortActionTriggered(void);
	//

	void setGrayScale(void);
	//void setGrayscale(bool);
	void His0ActionTriggered(void);
	void His1ActionTriggered(void);
	void His2ActionTriggered(void);
	void His3ActionTriggered(void);
	void His4ActionTriggered(void);
	void His5ActionTriggered(void);
private slots:
	void receiveSeed(double data);
	void receiveAngle(double data);
	void receiveTiltAngle(double dataX, double dataY);
signals:
	//void newProcessingFlags(struct ProcessingFlags p_flags);

};

#endif // IMAGEMAKER_H


