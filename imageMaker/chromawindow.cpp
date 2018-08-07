#include "chromawindow.h"

chromaWindow::chromaWindow(QWidget *parent)
	: QDialog(parent),
	mPHLSItem(0,0,0)
{
	this->setObjectName(QStringLiteral("Dialog"));
	this->resize(500, 350);
	this->setWindowTitle(QString::fromLocal8Bit("色度"));
	setupUi();
}

chromaWindow::~chromaWindow()
{

}

void chromaWindow::setupUi(void)
{
	pushButton_OK = new QPushButton(this);
	pushButton_OK->setObjectName(QStringLiteral("pushButton_OK"));
	pushButton_OK->setGeometry(QRect(350, 40, 120, 30));
	pushButton_Cancel = new QPushButton(this);
	pushButton_Cancel->setObjectName(QStringLiteral("pushButton_Cancel"));
	pushButton_Cancel->setGeometry(QRect(350, 90, 120, 30));
	pushButton_intiData = new QPushButton(this);
	pushButton_intiData->setObjectName(QStringLiteral("pushButton_intiData"));
	pushButton_intiData->setGeometry(QRect(350, 140, 120, 30));

	checkBox_Preview = new QCheckBox(this);
	checkBox_Preview->setObjectName(QStringLiteral("checkBox_Preview"));
	checkBox_Preview->setGeometry(QRect(350, 200, 120, 30));
	checkBox_Preview->setChecked(true);

	Slider_H = new QSlider(this);
	Slider_H->setObjectName(QStringLiteral("Slider_H"));
	Slider_H->setGeometry(QRect(50, 80, 270, 16));
	Slider_H->setMinimumSize(QSize(270, 0));
	Slider_H->setOrientation(Qt::Horizontal);
	Slider_S = new QSlider(this);
	Slider_S->setObjectName(QStringLiteral("Slider_S"));
	Slider_S->setGeometry(QRect(50, 140, 270, 16));
	Slider_S->setMinimumSize(QSize(270, 0));
	Slider_S->setOrientation(Qt::Horizontal);
	Slider_L= new QSlider(this);
	Slider_L->setObjectName(QStringLiteral("Slider_L"));
	Slider_L->setGeometry(QRect(50, 200, 270, 16));
	Slider_L->setMinimumSize(QSize(270, 0));
	Slider_L->setOrientation(Qt::Horizontal);

	Slider_H->setMinimum(-180);  // 最小值
	Slider_H->setMaximum(180);  // 最大值
	Slider_H->setSingleStep(1);  // 步长
	Slider_S->setMinimum(-100);  // 最小值
	Slider_S->setMaximum(100);  // 最大值
	Slider_S->setSingleStep(1);  // 步长
	Slider_L->setMinimum(-100);  // 最小值
	Slider_L->setMaximum(100);  // 最大值
	Slider_L->setSingleStep(1);  // 步长

	label_H = new QLabel(this);
	label_H->setObjectName(QStringLiteral("label"));
	label_H->setGeometry(QRect(50, 40, 60, 30));
	label_S = new QLabel(this);
	label_S->setObjectName(QStringLiteral("label_S"));
	label_S->setGeometry(QRect(50, 100, 60, 30));
	label_L = new QLabel(this);
	label_L->setObjectName(QStringLiteral("label_L"));
	label_L->setGeometry(QRect(50, 160, 60, 30));

	lineEdit_H = new QLineEdit(this);
	lineEdit_H->setObjectName(QStringLiteral("lineEdit_H"));
	lineEdit_H->setGeometry(QRect(220, 40, 100, 30));
	lineEdit_S = new QLineEdit(this);
	lineEdit_S->setObjectName(QStringLiteral("lineEdit_S"));
	lineEdit_S->setGeometry(QRect(220, 100, 100, 30));
	lineEdit_L = new QLineEdit(this);
	lineEdit_L->setObjectName(QStringLiteral("lineEdit_L"));
	lineEdit_L->setGeometry(QRect(220, 160, 100, 30));

	QIntValidator *QIntValidator1 = new QIntValidator(this);
	QIntValidator *QIntValidator2 = new QIntValidator(this);
	QIntValidator1->setRange(-180, 180);
	QIntValidator2->setRange(-100, 100);
	lineEdit_H->setValidator(QIntValidator1);
	lineEdit_S->setValidator(QIntValidator2);
	lineEdit_L->setValidator(QIntValidator2);

	checkBox_color = new QCheckBox(this);
	checkBox_color->setObjectName(QStringLiteral("checkBox_color"));
	checkBox_color->setGeometry(QRect(50, 250, 120, 30));

	retranslateUi();

	connect(Slider_H, SIGNAL(valueChanged(int)), this, SLOT(setValueH(int)));
	connect(Slider_S, SIGNAL(valueChanged(int)), this, SLOT(setValueS(int)));
	connect(Slider_L, SIGNAL(valueChanged(int)), this, SLOT(setValueL(int)));

	connect(lineEdit_H, SIGNAL(textEdited(QString)), this, SLOT(setSLiderValueH(void)));
	connect(lineEdit_S, SIGNAL(textEdited(QString)), this, SLOT(setSLiderValueS(void)));
	connect(lineEdit_L, SIGNAL(textEdited(QString)), this, SLOT(setSLiderValueL(void)));

	connect(pushButton_intiData, SIGNAL(clicked(bool)), this, SLOT(intiData(void)));
	connect(pushButton_OK, SIGNAL(clicked(bool)), this, SLOT(chromaWindowTriggered(void)));
	connect(pushButton_Cancel, SIGNAL(clicked(bool)), this, SLOT(close()));
} // setupUi

void chromaWindow::retranslateUi(void)
{
	pushButton_OK->setText(QApplication::translate("this", "ok", 0));
	pushButton_Cancel->setText(QApplication::translate("this", "\345\217\226\346\266\210", 0));
	pushButton_intiData->setText(QApplication::translate("this", "\345\210\235\346\234\237\345\200\274", 0));
	checkBox_Preview->setText(QApplication::translate("this", "\351\242\204\346\274\224", 0));
	label_H->setText(QApplication::translate("this", "H", 0));
	label_S->setText(QApplication::translate("this", "S", 0));
	label_L->setText(QApplication::translate("this", "L", 0));
	checkBox_color->setText(QString::fromLocal8Bit("彩色"));

	lineEdit_H->setText(QString::number(1));
	lineEdit_S->setText(QString::number(1));
	lineEdit_L->setText(QString::number(1));
} // retranslateUi

void chromaWindow::intiData(void)
{
	lineEdit_H->setText(QString::number(0));
	lineEdit_S->setText(QString::number(0));
	lineEdit_L->setText(QString::number(0));

	Slider_H->setValue(0);
	Slider_S->setValue(0);
	Slider_S->setValue(0);
	mPHLSItem.hue = 0;
	mPHLSItem.saturation = 0;
	mPHLSItem.lightness = 0;
	mPHLSItem.index = 0;
	mPHLSItem.setleftright(0);

	if (checkBox_Preview->isChecked()) emit PHLSItemChange(mPHLSItem, false);
}

void chromaWindow::setValueH(int _data)
{
	mPHLSItem.hue = _data;
	lineEdit_H->setText(QString::number(mPHLSItem.hue));
	if (checkBox_Preview->isChecked()) emit PHLSItemChange(mPHLSItem, false);
}
void chromaWindow::setValueS(int _data)
{
	mPHLSItem.saturation = _data;
	lineEdit_S->setText(QString::number(mPHLSItem.saturation));
	if (checkBox_Preview->isChecked()) emit PHLSItemChange(mPHLSItem, false);
}
void chromaWindow::setValueL(int _data)
{
	mPHLSItem.lightness = _data;
	lineEdit_L->setText(QString::number(mPHLSItem.lightness));
	if (checkBox_Preview->isChecked()) emit PHLSItemChange(mPHLSItem, false);
}

void chromaWindow::setSLiderValueH(void)
{
	QString Str_H = lineEdit_H->text();
	mPHLSItem.hue = Str_H.toFloat();
	Slider_H->setValue(mPHLSItem.hue);
	if (checkBox_Preview->isChecked()) emit PHLSItemChange(mPHLSItem, false);

}
void chromaWindow::setSLiderValueS(void)
{
	QString Str_S = lineEdit_S->text();
	mPHLSItem.saturation = Str_S.toFloat();
	Slider_S->setValue(mPHLSItem.saturation);
	if (checkBox_Preview->isChecked()) emit PHLSItemChange(mPHLSItem, false);
}
void chromaWindow::setSLiderValueL(void)
{
	QString Str_L = lineEdit_L->text();
	mPHLSItem.lightness = Str_L.toFloat();
	Slider_L->setValue(mPHLSItem.lightness);
	if (checkBox_Preview->isChecked()) emit PHLSItemChange(mPHLSItem, false);
}

void chromaWindow::chromaWindowTriggered(void)
{
	emit emit PHLSItemChange(mPHLSItem, true);
	this->close();
}

