#include "tiltwindow.h"

tiltWindow::tiltWindow(QWidget *parent)
	: QDialog(parent)
{
	this->setObjectName(QStringLiteral("TiltImg"));
	this->setWindowTitle(tr("TiltImg"));
	this->resize(400, 150);
	setupUi();
	retranslateUi();
}

tiltWindow::~tiltWindow()
{

}

void tiltWindow::setupUi(void)
{
	pushButton = new QPushButton(this);
	pushButton->setObjectName(QStringLiteral("tiltImg"));
	pushButton->setText(QString::fromLocal8Bit("确定"));
	pushButton->setGeometry(QRect(275, 75, 100, 50));

	lineEditX = new QLineEdit(this);
	lineEditX->setObjectName(QStringLiteral("lineEditX"));
	lineEditX->setPlaceholderText(QString::fromLocal8Bit("水平倾斜角度: 0~90"));
	lineEditX->setGeometry(QRect(25, 25, 200, 50));

	lineEditY = new QLineEdit(this);
	lineEditY->setObjectName(QStringLiteral("lineEditY"));
	lineEditY->setPlaceholderText(QString::fromLocal8Bit("垂直倾斜角度: 0~90"));
	lineEditY->setGeometry(QRect(25, 75, 200, 50));
	// 
	QDoubleValidator *doubleValidator = new QDoubleValidator(this);
	doubleValidator->setRange(0, 90);
	doubleValidator->setNotation(QDoubleValidator::StandardNotation);
	doubleValidator->setDecimals(2);
	lineEditX->setValidator(doubleValidator);
	lineEditY->setValidator(doubleValidator);


	connect(pushButton, SIGNAL(clicked(bool)), this, SLOT(tiltButtonopTriggered()));

} // setupUi

void tiltWindow::retranslateUi(void)
{

} // retranslateUi



void tiltWindow::tiltButtonopTriggered(void)
{
	QString textTempX = lineEditX->text(), textTempY = lineEditY->text();

	double AngleX = textTempX.toDouble(), AngleY = textTempY.toDouble();
	emit sendTiltAngle(AngleX, AngleY);
	this->close();
}
