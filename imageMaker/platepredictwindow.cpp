#include "platepredictwindow.h"

PlatePredictWindow::PlatePredictWindow(IplImage *inImg, QWidget *parent)
	: QDialog(parent)
{
	//this->carImg = new PlatePredict();
	//this->carImg->LoadImage(inImg);

	this->mploc.InitialData(inImg);

	this->setWindowTitle(tr("CarPlate"));
	if (this->objectName().isEmpty())
		this->setObjectName(QStringLiteral("Dialog"));
	this->resize(1000, 1000);
	setupUi();
	retranslateUi();
}

PlatePredictWindow::~PlatePredictWindow()
{

}

void PlatePredictWindow::setupUi()
{
	//int w_src = carImg->pixmap.width(), h_src = carImg->pixmap.height();
	int w_src = mploc.initialImg->width, h_src = mploc.initialImg->height;

	graphicsView = new QGraphicsView(this);
	graphicsView->setObjectName(QStringLiteral("graphicsView"));
	graphicsView->setGeometry(QRect(20, 20, 1000, 1000));

	scene = new QGraphicsScene;
	scene->addPixmap(Iplimage2Qpixmap(mploc.initialImg));
	graphicsView->setScene(scene);
	graphicsView->resize(w_src + 10, h_src + 10);
	graphicsView->show();

	this->resize(w_src + 350, h_src + 100);

	//graphicsView_2 = new QGraphicsView(this);
	//graphicsView_2->setObjectName(QStringLiteral("graphicsView_2"));
	//graphicsView_2->setGeometry(QRect(w_src + 50, 50, 111, 41));

	//label = new QLabel((QString::fromLocal8Bit("车牌位置: ")), this);
	//label->setObjectName(QStringLiteral("label"));
	//label->setGeometry(QRect(w_src + 50, 20, 100, 30));
	
	label_2 = new QLabel((QString::fromLocal8Bit("识别结果: ")), this);
	label_2->setObjectName(QStringLiteral("label_2"));
	label_2->setGeometry(QRect(w_src + 50, 20, 100, 30));

	textEdit = new QTextEdit(this);
	textEdit->setObjectName(QStringLiteral("textEdit"));
	textEdit->setGeometry(QRect(w_src + 50, 50, 300, 100));

	pushButton = new QPushButton((QString::fromLocal8Bit("定位识别")), this);
	pushButton->setObjectName(QStringLiteral("Location"));
	pushButton->setGeometry(QRect(w_src + 50, 160, 100, 30));

	connect(pushButton, SIGNAL(clicked(bool)), this, SLOT(LocateButtonopTriggered()));

	//QMetaObject::connectSlotsByName(this);

} // setupUi

void PlatePredictWindow::retranslateUi(void)
{

} // retranslateUi

void PlatePredictWindow::LocateButtonopTriggered(void)
{
	//carImg->FindPlateLocation();
	mploc.LocatePlate();

	scene->addPixmap(Iplimage2Qpixmap(mploc.locateImg));
	graphicsView->setScene(scene);
	graphicsView->show();

	vector<mPlate>::iterator iter;
	iter = mploc.candPlates.begin();
	while (iter != mploc.candPlates.end())
	{
		textEdit->append((QString::fromLocal8Bit("车牌：")));
		textEdit->append(QString::fromStdString(iter->getPlateString()) );
		//textEdit->append("\n");
		iter++;
	}

	/*carImg->FindPlateLocation();
	int w_src = carImg->pixmap.width(), h_src = carImg->pixmap.height();
	int w_plate = carImg->pixPlate.width()+20, h_plate = carImg->pixPlate.height()+20;

	graphicsView_2->setGeometry(QRect(w_src + 50, 50, w_plate, h_plate));
	label->setGeometry(QRect(w_src + 50, 20 + h_plate, 100, 30));
	label_2->setGeometry(QRect(w_src + 50, 100 + h_plate, 100, 30));
	textEdit->setGeometry(QRect(w_src + 50, 150 + h_plate, 150, 75));
	pushButton->setGeometry(QRect(w_src + 50, 260 + h_plate, 100, 30));
	pushButton_2->setGeometry(QRect(w_src + 50, 300 + h_plate, 100, 30));

	scene222 = new QGraphicsScene;
	scene222->addPixmap(carImg->pixPlate);
	graphicsView_2->setScene(scene222);
	graphicsView_2->show();*/

}