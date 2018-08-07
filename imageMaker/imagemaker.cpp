#include "imagemaker.h"

#include <QWidget>
#include <QImage>
#include <QFileDialog>
#include <QPixmap>
#include <QAction>
#include <QMessageBox>
#include <QDebug>
#include <QScrollArea>
#include <QGridLayout>
#include <QErrorMessage>
#include <QApplication>

imageMaker::imageMaker(QWidget *parent)
	: QMainWindow(parent)
{
	//init main window 
	initMainWindow();

	// init ui 
	initUiComponent();

	// init resource 
	initImageResource();

	//create imageViewer 
	imageViewer = new mImage();

	//������ʼ��
	//processingFlags.grayscaleOn = false;
}

imageMaker::~imageMaker()
{

}

void imageMaker::initMainWindow(void)
{
	menuBar = new QMenuBar(this);
	setMenuBar(menuBar);

	toolBar = new QToolBar(this);
	addToolBar(toolBar);

	centralWidget = new QWidget(this);
	setCentralWidget(centralWidget);

	statusBar = new QStatusBar(this);
	setStatusBar(statusBar);
}
void imageMaker::initUiComponent(void)
{
	// set menu and toolbar
	setWindowComponet();

	// image show widget
	setImageMakerViewerWidget();
}
void imageMaker::setImageMakerViewerWidget(void)
{
	//label show image 
	imageLabel = new QLabel();

	QScrollArea *imageScrollArea = new QScrollArea();
	imageScrollArea->setAlignment(Qt::AlignCenter);
	imageScrollArea->setFrameShape(QFrame::NoFrame);
	imageScrollArea->setWidget(imageLabel);

	QGridLayout *mainLayout = new QGridLayout();
	mainLayout->addWidget(imageScrollArea, 0, 0);
	centralWidget->setLayout(mainLayout);
}
void imageMaker::setWindowComponet(void)
{
	//�������� FileMenu--------------------------
    #pragma region 
	openAction = new QAction(tr("Open"), this);
	openAction->setShortcut(QKeySequence::Open);
	openAction->setStatusTip(tr("Open a image."));
	openAction->setIcon(QIcon("./Resources/openImageButton.png"));

	closeAction = new QAction(tr("Close"), this);
	closeAction->setShortcut(QKeySequence::Close);
	closeAction->setStatusTip(tr("Close a image."));
	closeAction->setIcon(QIcon("./Resources/closeFileButton.png"));

	saveAction = new QAction(tr("save"), this);
	saveAction->setShortcut(QKeySequence::Save);
	saveAction->setStatusTip(tr("save a image."));
	saveAction->setIcon(QIcon("./Resources/saveButton.png"));

	saveAsAction = new QAction(tr("saveAs"), this);
	saveAsAction->setShortcut(QKeySequence::SaveAs);
	saveAsAction->setStatusTip(tr("save as."));
	saveAsAction->setIcon(QIcon("./Resources/saveAsButton.png"));
    

	/*
	lastAction = new QAction(tr("Last"), this);
	lastAction->setStatusTip(tr("Last image."));
	lastAction->setIcon(QIcon(":/images/left.png"));

	nextAction = new QAction(tr("Next"), this);
	nextAction->setStatusTip(tr("Next image"));
	nextAction->setIcon(QIcon(":/images/right.png"));

	toLeftAction = new QAction(tr("LeftSpin"), this);
	toLeftAction->setStatusTip(tr("To Left."));
	toLeftAction->setIcon(QIcon(":/images/toLeft.png"));

	toRightAction = new QAction(tr("RightSpin"), this);
	toRightAction->setStatusTip(tr("To Right."));
	toRightAction->setIcon(QIcon(":/images/toRight.png"));

	toEnlargeAction = new QAction(tr("Enlarge"), this);
	toEnlargeAction->setStatusTip(tr("To Enlarge."));
	toEnlargeAction->setIcon(QIcon(":/images/large.png"));

	toLessenAction = new QAction(tr("Lessen"), this);
	toLessenAction->setStatusTip(tr("To Lessen."));
	toLessenAction->setIcon(QIcon(":/images/small.png"));

	deleteAction = new QAction(tr("Delete"), this);
	deleteAction->setStatusTip(tr("Delete a image"));
	deleteAction->setIcon(QIcon(":/images/clear.png"));
	deleteAction->setShortcut(QKeySequence::Delete);
	*/

	fileMenu = menuBar->addMenu(tr("File"));
	fileMenu->addAction(openAction);
	fileMenu->addAction(saveAction);
	fileMenu->addAction(saveAsAction);
	fileMenu->addAction(closeAction);
	fileMenu->addSeparator();

	toolBar->addAction(openAction);
	toolBar->addAction(closeAction);
	toolBar->addAction(saveAction);
	toolBar->addAction(saveAsAction);

	/*
	toolBar->addAction(lastAction);
	toolBar->addAction(nextAction);
	toolBar->addAction(toLeftAction);
	toolBar->addAction(toRightAction);
	toolBar->addAction(toEnlargeAction);
	toolBar->addAction(toLessenAction);
	toolBar->addAction(deleteAction);
	toolBar->addAction(about);*/

	connect(openAction, SIGNAL(triggered(bool)), this, SLOT(openActionTriggered()));
	connect(closeAction, SIGNAL(triggered(bool)), this, SLOT(closeActionTriggered()));
	connect(saveAction, SIGNAL(triggered(bool)), this, SLOT(saveActionTriggered()));
	connect(saveAsAction, SIGNAL(triggered(bool)), this, SLOT(saveAsActionTriggered()));
    #pragma endregion

	//ͼ�����--------------------
	menu_img_init();
	//�˲�����--------------------
	menu_filter_init();

	//���α任 FileMenu--------------------------
    #pragma region 

	QAction *resizeAction;
	QAction *rotateAction;
	QAction *tiltAction;

	resizeAction = new QAction((QString::fromLocal8Bit("����")), this);
	rotateAction = new QAction((QString::fromLocal8Bit("��ת")), this);
	tiltAction = new QAction((QString::fromLocal8Bit("��б")), this);

	resizeAction->setDisabled(true);


	QMenu *GEMenu = menuBar->addMenu((QString::fromLocal8Bit("���α任")));
	QMenu *WrapMenu;
	WrapMenu = new QMenu((QString::fromLocal8Bit("����任")), GEMenu);
	GEMenu->addAction(WrapMenu->menuAction());
	QMenu *ReflectMenu;
	ReflectMenu = new QMenu((QString::fromLocal8Bit("����任")), WrapMenu);
	WrapMenu->addAction(ReflectMenu->menuAction());

	WrapMenu->addAction(resizeAction);
	WrapMenu->addAction(rotateAction);
	WrapMenu->addAction(tiltAction);

	
	connect(resizeAction, SIGNAL(triggered(bool)), this, SLOT(resizeActionTriggered()));
	connect(rotateAction, SIGNAL(triggered(bool)), this, SLOT(rotateActionTriggered()));
	connect(tiltAction, SIGNAL(triggered(bool)), this, SLOT(tiltActionTriggered()));

	QAction *HMirrorAction;
	QAction *VMirrorAction;
	QAction *MirrorAction;

	HMirrorAction = new QAction((QString::fromLocal8Bit("ˮƽ����")), this);
	VMirrorAction = new QAction((QString::fromLocal8Bit("��ֱ����")), this);
	MirrorAction = new QAction((QString::fromLocal8Bit("�е㾵��")), this);

	ReflectMenu->addAction(HMirrorAction);
	ReflectMenu->addAction(VMirrorAction);
	ReflectMenu->addAction(MirrorAction);

	connect(HMirrorAction, SIGNAL(triggered(bool)), this, SLOT(HMirrortActionTriggered()));
	connect(VMirrorAction, SIGNAL(triggered(bool)), this, SLOT(VMirrortActionTriggered()));
	connect(MirrorAction, SIGNAL(triggered(bool)), this, SLOT(MirrortActionTriggered()));

   #pragma endregion 
	//��ɫ�任
	



	//���� ��Ϣ--------------------------
   #pragma region 
	QAction *aboutQt = new QAction(tr("About Qt"), this);
	aboutQt->setStatusTip(tr("About Qt"));
	aboutQt->setIcon(QIcon("./Resources/Qt.png"));

	QAction *about = new QAction(tr("About QImageViewer"), this);
	about->setStatusTip(tr("About QImageViewer"));
	about->setIcon(QIcon("./Resources/help.png"));

	QMenu *helpMenu = menuBar->addMenu(tr("Help"));
	helpMenu->addAction(aboutQt);
	helpMenu->addAction(about);
	connect(about, SIGNAL(triggered(bool)), this, SLOT(aboutTriggered()));
	connect(aboutQt, SIGNAL(triggered(bool)), this, SLOT(aboutQtTriggered()));
	//connect(exitAction, SIGNAL(triggered(bool)), this, SLOT(close()));
   #pragma endregion
	//��ʷ ��¼--------------------------
   #pragma region  
	
	his0 = new QAction(tr("------0"), this);
	his0->setStatusTip(tr("------"));

	his1 = new QAction(tr("------1"), this);
	his1->setStatusTip(tr("------"));

	his2 = new QAction(tr("------2"), this);
	his2->setStatusTip(tr("------"));

	his3 = new QAction(tr("------3"), this);
	his3->setStatusTip(tr("------"));

	his4 = new QAction(tr("------4"), this);
	his4->setStatusTip(tr("------"));

	his5= new QAction(tr("------5"), this);
	his5->setStatusTip(tr("------"));
	//QMenu *HistoryMenu = menuBar->addMenu(QString::fromLocal8Bit("��ʷ"));
	HistoryMenu = menuBar->addMenu(QString::fromLocal8Bit("��ʷ"));
	HistoryMenu->addAction(his0);
	HistoryMenu->addAction(his1);
	HistoryMenu->addAction(his2);
	HistoryMenu->addAction(his3);
	HistoryMenu->addAction(his4);
	HistoryMenu->addAction(his5);

	connect(his0, SIGNAL(triggered(bool)), this, SLOT(His0ActionTriggered()));
	connect(his1, SIGNAL(triggered(bool)), this, SLOT(His1ActionTriggered()));
	connect(his2, SIGNAL(triggered(bool)), this, SLOT(His2ActionTriggered()));
	connect(his3, SIGNAL(triggered(bool)), this, SLOT(His3ActionTriggered()));
	connect(his4, SIGNAL(triggered(bool)), this, SLOT(His4ActionTriggered()));
	connect(his5, SIGNAL(triggered(bool)), this, SLOT(His5ActionTriggered()));
   #pragma endregion

	//ttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt

	QAction *tensAction = new QAction(tr("Test"), this);
	tensAction->setStatusTip(tr("test a image."));
	tensAction->setIcon(QIcon("./Resources/test.png"));
	toolBar->addAction(tensAction);
	connect(tensAction, SIGNAL(triggered(bool)), this, SLOT(TestActionTriggered()));
	//tensAction->setEnabled(false);

	QAction *plateAction = new QAction(tr("carPlate"), this);
	plateAction->setStatusTip(tr("carPlate."));
	plateAction->setIcon(QIcon("./Resources/Car.png"));
	toolBar->addAction(plateAction);
	connect(plateAction, SIGNAL(triggered(bool)), this, SLOT(plateActionTriggered()));

	activeButton(false);
}
void imageMaker::initImageResource(void)
{
	imageLabel->clear();
	imageLabel->resize(QSize(800, 600));
	setWindowTitle(tr("ImageMaker"));
}
void imageMaker::loadImageResource(void)
{
	imageLabel->setPixmap(imageViewer->pixmap);
	imageLabel->resize(imageViewer->size);
	setWindowTitle(QFileInfo(imageViewer->filename).fileName() + tr(" - ImageMaker"));
}
//menu img initial---------------------------------------------------------------------------
void imageMaker::menu_img_init(void)
{
	imgMenu = menuBar->addMenu((QString::fromLocal8Bit("ͼ��(Img)")));
	
	dimensionsAction = new QAction((QString::fromLocal8Bit("ͼ��ߴ�")), this);
	analyticdegreeAction = new QAction((QString::fromLocal8Bit("ͼ�������")), this);	
	L2R_Action = new QAction((QString::fromLocal8Bit("���ҷ�ת")), this);
	U2D_Action = new QAction((QString::fromLocal8Bit("���·�ת")), this);
	Rorate90Action = new QAction((QString::fromLocal8Bit("90����ת(˳ʱ��)")), this);
	Rorate90BAction = new QAction((QString::fromLocal8Bit("90����ת(��ʱ��)")), this);
	Rorate180Action = new QAction((QString::fromLocal8Bit("180����ת(˳ʱ��)")), this);
	antiColorAction = new QAction((QString::fromLocal8Bit("ɫ����ת")), this);
	backGroundColorAction = new QAction((QString::fromLocal8Bit("ͼ�񱳾���ɫ")), this);
	
	imgMenu->addAction(dimensionsAction);
	imgMenu->addAction(analyticdegreeAction);
	imgMenu->addSeparator();
	imgMenu->addAction(L2R_Action);
	imgMenu->addAction(U2D_Action);
	imgMenu->addSeparator();
	imgMenu->addAction(Rorate90Action);
	imgMenu->addAction(Rorate90BAction);
	imgMenu->addAction(Rorate180Action);
	imgMenu->addSeparator();
	imgMenu->addAction(antiColorAction);
	imgMenu->addAction(backGroundColorAction);

	connect(dimensionsAction, SIGNAL(triggered(bool)), this, SLOT(dimensionsActionTriggered()));
	connect(analyticdegreeAction, SIGNAL(triggered(bool)), this, SLOT(analyticdegreeActionTriggered()));
	connect(L2R_Action, SIGNAL(triggered(bool)), this, SLOT(hflipActionTriggered()));
	connect(U2D_Action, SIGNAL(triggered(bool)), this, SLOT(vflipActionTriggered()));
	connect(Rorate90Action, SIGNAL(triggered(bool)), this, SLOT(Rorate90ActionTriggered()));
	connect(Rorate90BAction, SIGNAL(triggered(bool)), this, SLOT(Rorate90BActionTriggered()));
	connect(Rorate180Action, SIGNAL(triggered(bool)), this, SLOT(Rorate180ActionTriggered()));
	connect(antiColorAction, SIGNAL(triggered(bool)), this, SLOT(antiColorActionTriggered()));
}

void imageMaker::dimensionsActionTriggered(void)
{
	dimensionsWindow * _dimensionsWindow = new dimensionsWindow(imageViewer->currentImage->width, imageViewer->currentImage->height);
	//�����źźͲۺ���  
	connect(_dimensionsWindow, SIGNAL(send_w_h(int, int,int)), this, SLOT(receiveDimensions(int , int ,int)));
	_dimensionsWindow->exec();

	refreshImgviewer("- Rdimensions");
}
void imageMaker::receiveDimensions(int _w, int _h,int _flag)
{
	imageViewer->currentImageTemp = expandImage(imageViewer->currentImage, _w, _h, 255, _flag);
	imageViewer->loadImageResource(imageViewer->currentImageTemp);
}

void imageMaker::analyticdegreeActionTriggered(void)
{
	analyticDegreeWindow * _analyticDegreeWindow = new analyticDegreeWindow(imageViewer->currentImage->width, imageViewer->currentImage->height);
	//�����źźͲۺ���  
	connect(_analyticDegreeWindow, SIGNAL(send_w_h(int, int)), this, SLOT(receiveAnalyticDegree(int, int)));
	_analyticDegreeWindow->exec();

	refreshImgviewer("- Resize");
}
void imageMaker::receiveAnalyticDegree(int _w, int _h)
{
	imageViewer->currentImageTemp = resizeImgage(imageViewer->currentImage, _w, _h);
	imageViewer->loadImageResource(imageViewer->currentImageTemp);
}

void imageMaker::hflipActionTriggered(void)
{
	mirrorImage(imageViewer->currentImage, imageViewer->currentImageTemp, 0);
	imageViewer->loadImageResource(imageViewer->currentImageTemp);
	refreshImgviewer("- Left2Right");
}
void imageMaker::vflipActionTriggered(void)
{
	mirrorImage(imageViewer->currentImage, imageViewer->currentImageTemp, 1);
	imageViewer->loadImageResource(imageViewer->currentImageTemp);
	refreshImgviewer("- Up2Down");
}

void imageMaker::Rorate180ActionTriggered(void)
{
	imageViewer->currentImageTemp = rotateImgage(imageViewer->currentImage, 180.);
	imageViewer->loadImageResource(imageViewer->currentImageTemp);
	refreshImgviewer("- rotate 180��");
}
void imageMaker::Rorate90BActionTriggered(void)
{
	imageViewer->currentImageTemp = rotateImgage(imageViewer->currentImage, 90);
	imageViewer->loadImageResource(imageViewer->currentImageTemp);
	refreshImgviewer("- rotate 180��");
}
void imageMaker::Rorate90ActionTriggered(void)
{
	imageViewer->currentImageTemp = rotateImgage(imageViewer->currentImage, -90);
	imageViewer->loadImageResource(imageViewer->currentImageTemp);
	refreshImgviewer("- rotate 180��");
}

void imageMaker::antiColorActionTriggered(void)
{
	antiImgColor(imageViewer->currentImage, imageViewer->currentImageTemp);
	imageViewer->loadImageResource(imageViewer->currentImageTemp);
	refreshImgviewer("- anti color��");
}
//menu Filter initial--------------------------------------------------------------
void imageMaker::menu_filter_init(void)
{
	filterMenu = menuBar->addMenu((QString::fromLocal8Bit("�˾�(T)")));
	
	toneMenu = new QMenu((QString::fromLocal8Bit("ɫ������")), filterMenu);

	colorbandsAction = new QAction((QString::fromLocal8Bit("ɫ�ײ���")), this);
	colorbalanceAction = new QAction((QString::fromLocal8Bit("ɫ��ƽ��")), this);
	brightnessAction= new QAction((QString::fromLocal8Bit("����/�Աȶ�")), this);
	chromaAction = new QAction((QString::fromLocal8Bit("ɫ��/�ʶ�")), this);
	grayScaleAction = new QAction((QString::fromLocal8Bit("�Ҷ�")), this);
	grayScaleAction->setStatusTip("Gray Scale image.");
	grayScaleAction->setIcon(QIcon("./Resources/transparencyToolStripMenuItem.png"));
	blackwhilteThreshAction = new QAction((QString::fromLocal8Bit("�ڰ���ֵ")), this);
	
	filterMenu->addAction(toneMenu->menuAction());

	toneMenu->addAction(colorbandsAction);
	toneMenu->addAction(colorbalanceAction);
	toneMenu->addAction(brightnessAction);
	toneMenu->addAction(chromaAction);
	toneMenu->addAction(grayScaleAction);
	toneMenu->addSeparator();
	toneMenu->addAction(antiColorAction);
	toneMenu->addAction(blackwhilteThreshAction);
	
	connect(colorbandsAction, SIGNAL(triggered(bool)), this, SLOT(colorbandsActionTriggered()));
	connect(colorbalanceAction, SIGNAL(triggered(bool)), this, SLOT(colorbalanceActionTriggered()));
	connect(brightnessAction, SIGNAL(triggered(bool)), this, SLOT(brightnessActionTriggered()));
	connect(chromaAction, SIGNAL(triggered(bool)), this, SLOT(chromaActionTriggered()));
	connect(grayScaleAction, SIGNAL(triggered(bool)), this, SLOT(setGrayScale()));
	connect(blackwhilteThreshAction, SIGNAL(triggered(bool)), this, SLOT(blackwhilteThreshActionTriggered()));

}

void imageMaker::colorbandsActionTriggered(void)
{
	mMatrix<size_t> hist= getImgHistorm(imageViewer->currentImage);

	colorbandsWindow * _colorbandsWindow = new colorbandsWindow(&hist);
	//�����źźͲۺ���  
	connect(_colorbandsWindow, SIGNAL(PColorLevelItemChange(PColorLevelItem,bool)), this, SLOT(receivePColorLevelItem(PColorLevelItem,bool)));
	_colorbandsWindow->exec();

	refreshImgviewer("- ColorBand");
}
void imageMaker::receivePColorLevelItem(PColorLevelItem _data,bool _act)
{
	cvCopy(imageViewer->currentImage, imageViewer->currentImageTemp);
	imageColorLevel(imageViewer->currentImage, imageViewer->currentImageTemp, _data, 0);
	

	if (_act){
		imageViewer->loadImageResource(imageViewer->currentImageTemp);
	}
	else{
		QPixmap tempPix = Iplimage2Qpixmap(imageViewer->currentImageTemp);
		imageLabel->setPixmap(tempPix);
		imageLabel->resize(tempPix.size());
		setWindowTitle(QFileInfo(imageViewer->filename).fileName() + tr("temp"));
	}
}

void imageMaker::colorbalanceActionTriggered(void)
{
	colorBalanceWindow * _colorBalanceWindow = new colorBalanceWindow(this);
	//�����źźͲۺ���  
	//connect(_colorBalanceWindow, SIGNAL(PColorLevelItemChange(PColorLevelItem, bool)), this, SLOT(receivePColorLevelItem(PColorLevelItem, bool)));
	_colorBalanceWindow->exec();
}

void imageMaker::brightnessActionTriggered(void)
{
	brightnessWindow * _brightnessWindow = new brightnessWindow(this);
	connect(_brightnessWindow, SIGNAL(send_Brightness_Contrast(PBrightContrastItem, bool)), this, SLOT(receiveBrightnessContrast(PBrightContrastItem, bool)));
	_brightnessWindow->exec();
	refreshImgviewer("- set Brightness Contrast��");
}
void imageMaker::receiveBrightnessContrast(PBrightContrastItem _PBrightContrastItem, bool _act)
{
	adjustBrightnessContrast(imageViewer->currentImage, imageViewer->currentImageTemp, _PBrightContrastItem);

	if (_act){
		imageViewer->loadImageResource(imageViewer->currentImageTemp);
	}
	else{
		QPixmap tempPix = Iplimage2Qpixmap(imageViewer->currentImageTemp);
		imageLabel->setPixmap(tempPix);
		imageLabel->resize(tempPix.size());
		setWindowTitle(QFileInfo(imageViewer->filename).fileName() + tr("temp"));
	}
}
	
void imageMaker::chromaActionTriggered(void)
{
	chromaWindow * _chromaWindow = new chromaWindow(this);
	connect(_chromaWindow, SIGNAL(PHLSItemChange(PHLSItem, bool)), this, SLOT(receivePHLSItem(PHLSItem, bool)));
	_chromaWindow->exec();
	refreshImgviewer("- set HSL");
}
void imageMaker::receivePHLSItem(PHLSItem _PHLSItem, bool _act)
{
	adjustHSL(imageViewer->currentImage, imageViewer->currentImageTemp, _PHLSItem);

	if (_act){
		imageViewer->loadImageResource(imageViewer->currentImageTemp);
	}
	else{
		QPixmap tempPix = Iplimage2Qpixmap(imageViewer->currentImageTemp);
		imageLabel->setPixmap(tempPix);
		imageLabel->resize(tempPix.size());
		setWindowTitle(QFileInfo(imageViewer->filename).fileName() + tr("temp"));
	}
}

void imageMaker::setGrayScale()
{
	imageViewer->currentImageTemp = cvCreateImage(cvGetSize(imageViewer->currentImage), imageViewer->currentImage->depth, 1);
	grayScaleImage(imageViewer->currentImage, imageViewer->currentImageTemp);

	imageViewer->loadImageResource(imageViewer->currentImageTemp);
	refreshImgviewer("- set gray scale");
}

void  imageMaker::blackwhilteThreshActionTriggered(void)
{
	mMatrix<size_t> hist = getImgHistorm(imageViewer->currentImage);

	blackwhilteThreshWindow * _blackwhilteThreshWindow = new blackwhilteThreshWindow(&hist);
	//�����źźͲۺ���  
	connect(_blackwhilteThreshWindow, SIGNAL(ThreshChanged(int, bool)), this, SLOT(receiveThresh(int, bool)));
	_blackwhilteThreshWindow->exec();
	refreshImgviewer("- set Thresh");
}
void imageMaker::receiveThresh(int _thresh, bool _act){
	IplImage *temp = cvCreateImage(cvGetSize(imageViewer->currentImage), imageViewer->currentImage->depth, 1);
	
	grayScaleImage(imageViewer->currentImage, temp);
	cvThreshold(temp, temp, _thresh, 255, CV_THRESH_BINARY);
	
	if (_act){
		imageViewer->currentImageTemp = cvCreateImage(cvGetSize(imageViewer->currentImage), imageViewer->currentImage->depth, 1);
		imageViewer->currentImageTemp = temp;
		imageViewer->loadImageResource(imageViewer->currentImageTemp);
		refreshImgviewer("- set Thresh");
	}
	else{
		QPixmap tempPix = Iplimage2Qpixmap(temp);
		imageLabel->setPixmap(tempPix);
		imageLabel->resize(tempPix.size());
		setWindowTitle(QFileInfo(imageViewer->filename).fileName() + tr("temp"));
	}
}

	
//��ʷ��¼---------------------------------------------------------------------------
void imageMaker::historyOperate(void)
{
	if (this->hisCount < this->hisMax)
	{
		hisImage.push_back(*(this->imageViewer->currentImage));
		hisFileName.push_back((this->imageViewer->filename));
		hisPixmap.push_back(this->imageViewer->pixmap);
		this->hisCount++;
	}
	else
	{
		hisImage.pop_front();
		hisImage.push_back(*(this->imageViewer->currentImage));
		hisFileName.pop_front();
		hisFileName.push_back((this->imageViewer->filename));
		hisPixmap.pop_front();
		hisPixmap.push_back(this->imageViewer->pixmap);
	}
	updateHisTags();
}
void imageMaker::updateHisTags(void)
{

}

//��������
void imageMaker::openActionTriggered(void)
{
	int ret = imageViewer->openImageFile(tr("Select image:"),
		"C:\\Users\\zhang\\Pictures",
		tr("Images (*.jpg *.jpeg *.png *.bmp *.gif)"));
	if (ret) {
		QMessageBox::information(this, tr("Error"), tr("Open a file failed!"));
		return;
	}

	historyOperate();
	loadImageResource();

	activeButton(true);
	//updateHisTags();
}

void imageMaker::closeActionTriggered(void)
{
	initImageResource();
	imageViewer->closeImageFile();
	activeButton(false);
}

void imageMaker::saveActionTriggered(void)
{
	this->imageViewer->saveImageFile();
}

void imageMaker::saveAsActionTriggered(void)
{
	this->imageViewer->saveAsImageFile();
}

//����opencv��һЩͼ����
void imageMaker::resizeActionTriggered()
{	
	//double seedx, seedy;

	resizeWindow * _resizeWindow = new resizeWindow();
	//�����źźͲۺ���  
	connect(_resizeWindow, SIGNAL(sendSeed(double)), this, SLOT(receiveSeed(double)));
	//_resizeWindow->show();
	_resizeWindow->exec();
	//seedy = seedx;

	
	imageLabel->setPixmap(imageViewer->pixmap);
	imageLabel->resize(imageViewer->pixmap.size());
	setWindowTitle(QFileInfo(imageViewer->filename).fileName() + tr(" - Resize"));
}
void imageMaker::receiveSeed(double data)
{
	imageViewer->resizeImgage(data, data);
}

void imageMaker::rotateActionTriggered()
{
	rotateWindow * _rotateWindow = new rotateWindow();
	//�����źźͲۺ���  
	connect(_rotateWindow, SIGNAL(sendAngle(double)), this, SLOT(receiveAngle(double)));
	_rotateWindow->exec();

	imageLabel->setPixmap(imageViewer->pixmap);
	imageLabel->resize(imageViewer->pixmap.size());
	setWindowTitle(QFileInfo(imageViewer->filename).fileName() + tr(" - Rotate"));
}
void imageMaker::receiveAngle(double data)
{
	imageViewer->rotateImgage(data);
}

void imageMaker::tiltActionTriggered()
{
	tiltWindow * _tiltWindow = new tiltWindow();
	//�����źźͲۺ���  
	connect(_tiltWindow, SIGNAL(sendTiltAngle(double, double)), this, SLOT(receiveTiltAngle(double, double)));
	_tiltWindow->exec();

	imageLabel->setPixmap(imageViewer->pixmap);
	imageLabel->resize(imageViewer->pixmap.size());
	setWindowTitle(QFileInfo(imageViewer->filename).fileName() + tr(" - Tilt"));
}
void imageMaker::receiveTiltAngle(double dataX, double dataY)
{
	imageViewer->skewImage(dataX, dataY);
}
void imageMaker::HMirrortActionTriggered(void)
{
	imageViewer->mirrorImage(0);
	imageLabel->setPixmap(imageViewer->pixmap);
	imageLabel->resize(imageViewer->pixmap.size());
	setWindowTitle(QFileInfo(imageViewer->filename).fileName() + tr(" - Mirror"));
}
void imageMaker::VMirrortActionTriggered(void)
{
	imageViewer->mirrorImage(1);
	imageLabel->setPixmap(imageViewer->pixmap);
	imageLabel->resize(imageViewer->pixmap.size());
	setWindowTitle(QFileInfo(imageViewer->filename).fileName() + tr(" - Mirror"));
}
void imageMaker::MirrortActionTriggered(void)
{
	imageViewer->mirrorImage(2);
	imageLabel->setPixmap(imageViewer->pixmap);
	imageLabel->resize(imageViewer->pixmap.size());
	setWindowTitle(QFileInfo(imageViewer->filename).fileName() + tr(" - Mirror"));
}

//help�˵�
void imageMaker::aboutQtTriggered(void)
{
	qApp->aboutQt();
}

void imageMaker::aboutTriggered(void)
{
	aboutWidget.setWindowTitle("Help Infomation");
	aboutWidget.setWindowIcon(QIcon("./Resources/help.png"));
	aboutWidget.setFixedSize(MQABOUT_WIDGET_WIDTH, MQABOUT_WIDGET_HEIGHT);

	aboutWidget.show();
}
//��ʷ��¼
#pragma region
void imageMaker::His0ActionTriggered(void)
{
	std::list<QPixmap>::iterator iter = hisPixmap.begin();
	//advance(iter, num);

	imageLabel->setPixmap(*iter);
	imageLabel->resize(iter->size());
	setWindowTitle(QFileInfo(imageViewer->filename).fileName() + tr(" - ImageMaker"));
}
void imageMaker::His1ActionTriggered(void)
{
	std::list<QPixmap>::iterator iter = hisPixmap.begin();
	advance(iter, 1);

	imageLabel->setPixmap(*iter);
	imageLabel->resize(iter->size());
	setWindowTitle(QFileInfo(imageViewer->filename).fileName() + tr(" - ImageMaker"));
}
void imageMaker::His2ActionTriggered(void)
{
	std::list<QPixmap>::iterator iter = hisPixmap.begin();
	advance(iter, 2);

	imageLabel->setPixmap(*iter);
	imageLabel->resize(iter->size());
	setWindowTitle(QFileInfo(imageViewer->filename).fileName() + tr(" - ImageMaker"));
}
void imageMaker::His3ActionTriggered(void)
{
	std::list<QPixmap>::iterator iter = hisPixmap.begin();
	advance(iter, 3);

	imageLabel->setPixmap(*iter);
	imageLabel->resize(iter->size());
	setWindowTitle(QFileInfo(imageViewer->filename).fileName() + tr(" - ImageMaker"));
}
void imageMaker::His4ActionTriggered(void)
{
	std::list<QPixmap>::iterator iter = hisPixmap.begin();
	advance(iter, 4);

	imageLabel->setPixmap(*iter);
	imageLabel->resize(iter->size());
	setWindowTitle(QFileInfo(imageViewer->filename).fileName() + tr(" - ImageMaker"));
}
void imageMaker::His5ActionTriggered(void)
{
	std::list<QPixmap>::iterator iter = hisPixmap.begin();
	advance(iter, 5);

	imageLabel->setPixmap(*iter);
	imageLabel->resize(iter->size());
	setWindowTitle(QFileInfo(imageViewer->filename).fileName() + tr(" - ImageMaker"));
}
#pragma endregion

/*
void imageMaker::setGrayscale(bool input)
{
	
	// Not checked
	if (!input)
		processingFlags.grayscaleOn = false;
	// Checked
	else if (input)
		processingFlags.grayscaleOn = true;
	// Update processing flags in processingThread
	emit newProcessingFlags(processingFlags);

	

}

void imageMaker::newProcessingFlags(struct ProcessingFlags p_flags)
{

}*/
//����ʶ��
void imageMaker::plateActionTriggered(void)
{
	PlatePredictWindow * _platePredictWindow = new PlatePredictWindow(imageViewer->currentImage);
	_platePredictWindow->show();

}

void imageMaker::TestActionTriggered(void)
{
	imageViewer->perspectiveImage();
	imageLabel->setPixmap(imageViewer->pixmap);
	imageLabel->resize(imageViewer->size);
	setWindowTitle(QFileInfo(imageViewer->filename).fileName() + tr(" - GrayScale"));
}

//����ͼƬ
void imageMaker::refreshImgviewer(char * name)
{
	imageLabel->setPixmap(imageViewer->pixmap);
	imageLabel->resize(imageViewer->pixmap.size());
	setWindowTitle(QFileInfo(imageViewer->filename).fileName() + tr(name));
}

void imageMaker::activeButton(bool _state)
{
	if (!_state){
		saveAction->setDisabled(true);
		saveAsAction->setDisabled(true);

		dimensionsAction->setDisabled(true);
		analyticdegreeAction->setDisabled(true);
		L2R_Action->setDisabled(true);
		U2D_Action->setDisabled(true);
		Rorate90Action->setDisabled(true);
		Rorate90BAction->setDisabled(true);
		Rorate180Action->setDisabled(true);
		antiColorAction->setDisabled(true);
		backGroundColorAction->setDisabled(true);

		colorbandsAction->setDisabled(true);
		colorbalanceAction->setDisabled(true);
		brightnessAction->setDisabled(true);
		chromaAction->setDisabled(true);
		grayScaleAction->setDisabled(true);
		blackwhilteThreshAction->setDisabled(true);
	}
	else{
		saveAction->setDisabled(false);
		saveAsAction->setDisabled(false);

		dimensionsAction->setDisabled(false);
		analyticdegreeAction->setDisabled(false);
		L2R_Action->setDisabled(false);
		U2D_Action->setDisabled(false);
		Rorate90Action->setDisabled(false);
		Rorate90BAction->setDisabled(false);
		Rorate180Action->setDisabled(false);
		antiColorAction->setDisabled(false);
		backGroundColorAction->setDisabled(false);

		colorbandsAction->setDisabled(false);
		colorbalanceAction->setDisabled(false);
		brightnessAction->setDisabled(false);
		chromaAction->setDisabled(false);
		grayScaleAction->setDisabled(false);
		blackwhilteThreshAction->setDisabled(false);
	}

	 
}