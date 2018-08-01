#include "rotatewindow.h"


rotateWindow::rotateWindow(QWidget *parent)
	: QDialog(parent)
{
	this->setObjectName(QStringLiteral("RotateImg"));
	this->setWindowTitle(tr("RotateImg"));
	this->resize(400, 100);
	setupUi();
	retranslateUi();
}

rotateWindow::~rotateWindow()
{

}

void rotateWindow::setupUi(void)
{
	pushButton = new QPushButton(this);
	pushButton->setObjectName(QStringLiteral("RotateImg"));
	pushButton->setText(QString::fromLocal8Bit("确定"));
	pushButton->setGeometry(QRect(275, 25, 100, 50));

	lineEdit = new QLineEdit(this);
	lineEdit->setObjectName(QStringLiteral("lineEdit"));
	lineEdit->setPlaceholderText(QString::fromLocal8Bit("旋转角度: 0~360"));
	lineEdit->setGeometry(QRect(25, 25, 200, 50));
	// 
	QDoubleValidator *doubleValidator = new QDoubleValidator(this);

	doubleValidator->setRange(-360, 360);
	doubleValidator->setNotation(QDoubleValidator::StandardNotation);
	doubleValidator->setDecimals(2);
	lineEdit->setValidator(doubleValidator);


	connect(pushButton, SIGNAL(clicked(bool)), this, SLOT(rotateButtonopTriggered()));

} // setupUi

void rotateWindow::retranslateUi(void)
{

} // retranslateUi



void rotateWindow::rotateButtonopTriggered(void)
{
	QString textTemp = lineEdit->text();
	double Angle = textTemp.toDouble();
	emit sendAngle(Angle);
	this->close();
}

