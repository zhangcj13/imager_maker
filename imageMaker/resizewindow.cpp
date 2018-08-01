#include "resizewindow.h"

resizeWindow::resizeWindow(QWidget *parent)
	: QDialog(parent)
{
	this->setObjectName(QStringLiteral("ResizeImg"));
	this->setWindowTitle(tr("ResizeImg"));
	this->resize(400, 100);
	setupUi();
	retranslateUi();
}

resizeWindow::~resizeWindow()
{

}

void resizeWindow::setupUi(void)
{
	
	//pushButton = new QPushButton(this);
	pushButton = new QPushButton(this);
	pushButton->setObjectName(QStringLiteral("ResizeImg"));
	pushButton->setText(QString::fromLocal8Bit("确定"));
	pushButton->setGeometry(QRect(275, 25, 100, 50));
	
	lineEdit = new QLineEdit(this);
	lineEdit->setObjectName(QStringLiteral("lineEdit"));
	lineEdit->setPlaceholderText(QString::fromLocal8Bit("缩放系数: 0~100"));
	lineEdit->setGeometry(QRect(25, 25, 200, 50));
	// 浮点型 范围：[-0-100] 精度：小数点后2位
	QDoubleValidator *doubleValidator = new QDoubleValidator(this);

	doubleValidator->setRange(0, 100);
	doubleValidator->setNotation(QDoubleValidator::StandardNotation);
	doubleValidator->setDecimals(2);
	lineEdit->setValidator(doubleValidator);


	connect(pushButton, SIGNAL(clicked(bool)), this, SLOT(resizeButtonopTriggered()));
	//retranslateUi(Dialog);

	//QMetaObject::connectSlotsByName(Dialog
	
} // setupUi

void resizeWindow::retranslateUi(void)
{
	
	//this->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0));
	//pushButton->setText(QApplication::translate("Dialog", "PushButton", 0));
	
} // retranslateUi

/*
IplImage* resizeWindow::resizeImg(IplImage* imgin, double seedx, double seedy)
{
	CvSize size;
	size.height = int(imgin->height * seedx);
	size.width = int(imgin->width * seedy);
	IplImage* dst=cvCreateImage(size, imgin->depth, imgin->nChannels);
	cvResize(imgin, dst, CV_INTER_LINEAR);
	return dst;
}*/
//slot

void resizeWindow::resizeButtonopTriggered(void)
{
	QString textTemp = lineEdit->text();
	double seed = textTemp.toDouble();
	emit sendSeed(seed);
	this->close();
	//lineEdit->text
}

