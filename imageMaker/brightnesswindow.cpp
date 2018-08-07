#include "brightnesswindow.h"

brightnessWindow::brightnessWindow(QWidget *parent)
	: QDialog(parent),
	mPBrightContrastItem(0,0,0)
{
	this->setObjectName(QStringLiteral("Dialog"));
	this->resize(500, 320);
	this->setWindowTitle(QString::fromLocal8Bit("亮度/对比度"));
	setupUi();
}

brightnessWindow::~brightnessWindow()
{

}

void brightnessWindow::setupUi(void)
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

	Slider_brightness = new QSlider(this);
	Slider_brightness->setObjectName(QStringLiteral("Slider_brightness"));
	Slider_brightness->setGeometry(QRect(50, 80, 270, 16));
	Slider_brightness->setMinimumSize(QSize(270, 0));
	Slider_brightness->setOrientation(Qt::Horizontal);
	Slider_contrast = new QSlider(this);
	Slider_contrast->setObjectName(QStringLiteral("Slider_contrast"));
	Slider_contrast->setGeometry(QRect(50, 140, 270, 16));
	Slider_contrast->setMinimumSize(QSize(270, 0));
	Slider_contrast->setOrientation(Qt::Horizontal);

	Slider_brightness->setMinimum(-100);  // 最小值
	Slider_brightness->setMaximum(100);  // 最大值
	Slider_brightness->setSingleStep(1);  // 步长
	Slider_contrast->setMinimum(-100);  // 最小值
	Slider_contrast->setMaximum(100);  // 最大值
	Slider_contrast->setSingleStep(1);  // 步长

	label_brightness = new QLabel(this);
	label_brightness->setObjectName(QStringLiteral("label_brightness"));
	label_brightness->setGeometry(QRect(50, 40, 60, 30));
	label_contrast = new QLabel(this);
	label_contrast->setObjectName(QStringLiteral("label_contrast"));
	label_contrast->setGeometry(QRect(50, 100, 60, 30));

	lineEdit_brightness = new QLineEdit(this);
	lineEdit_brightness->setObjectName(QStringLiteral("lineEdit_brightness"));
	lineEdit_brightness->setGeometry(QRect(220, 40, 100, 30));
	lineEdit_contrast = new QLineEdit(this);
	lineEdit_contrast->setObjectName(QStringLiteral("lineEdit_contrast"));
	lineEdit_contrast->setGeometry(QRect(220, 100, 100, 30));

	//checkBox_linear = new QCheckBox(this);
	//checkBox_linear->setObjectName(QStringLiteral("checkBox_linear"));
	//checkBox_linear->setGeometry(QRect(50, 200, 120, 30));

	retranslateUi();

	connect(Slider_brightness, SIGNAL(valueChanged(int)), this, SLOT(setValueBrightness(int)));
	connect(Slider_contrast, SIGNAL(valueChanged(int)), this, SLOT(setValueContrast(int)));

	connect(lineEdit_brightness, SIGNAL(textEdited(QString)), this, SLOT(setSLiderValueBrightness(void)));
	connect(lineEdit_contrast, SIGNAL(textEdited(QString)), this, SLOT(setSLiderValueContrast(void)));

	connect(pushButton_intiData, SIGNAL(clicked(bool)), this, SLOT(intiData(void)));
	connect(pushButton_OK, SIGNAL(clicked(bool)), this, SLOT(brightnesswindowTriggered(void)));
	connect(pushButton_Cancel, SIGNAL(clicked(bool)), this, SLOT(close()));

} // setupUi

void brightnessWindow::retranslateUi(void)
{
	pushButton_OK->setText(QApplication::translate("Dialog", "ok", 0));
	pushButton_Cancel->setText(QApplication::translate("Dialog", "\345\217\226\346\266\210", 0));
	pushButton_intiData->setText(QApplication::translate("Dialog", "\345\210\235\346\234\237\345\200\274", 0));
	checkBox_Preview->setText(QApplication::translate("Dialog", "\351\242\204\346\274\224", 0));
	label_brightness->setText(QApplication::translate("Dialog", "\344\272\256\345\272\246", 0));
	label_contrast->setText(QApplication::translate("Dialog", "\345\257\271\346\257\224\345\272\246", 0));
	//checkBox_linear->setText(QApplication::translate("Dialog", "\347\272\277\345\275\242", 0));

	lineEdit_brightness->setText(QString::number(0));
	lineEdit_contrast->setText(QString::number(0));
} // retranslateUi

void brightnessWindow::intiData(void)
{
	lineEdit_brightness->setText(QString::number(0));
	lineEdit_contrast->setText(QString::number(0));
	Slider_brightness->setValue(0);
	Slider_contrast->setValue(0);

	mPBrightContrastItem.brightness = 0;
	mPBrightContrastItem.contrast = 0;
	mPBrightContrastItem.mode = 0;

	if (checkBox_Preview->isChecked()) emit send_Brightness_Contrast(mPBrightContrastItem, false);
}

void brightnessWindow::setValueBrightness(int _data){
	mPBrightContrastItem.brightness = (float)_data / 100;
	lineEdit_brightness->setText(QString::number(mPBrightContrastItem.brightness, 'f', 2));
	if (checkBox_Preview->isChecked()) emit send_Brightness_Contrast(mPBrightContrastItem, false);
}
void brightnessWindow::setValueContrast(int _data){
	mPBrightContrastItem.contrast = (float)_data / 100;
	lineEdit_contrast->setText(QString::number(mPBrightContrastItem.contrast, 'f', 2));
	if (checkBox_Preview->isChecked()) emit send_Brightness_Contrast(mPBrightContrastItem, false);
}

void brightnessWindow::setSLiderValueBrightness(void){
	QString Str_B = lineEdit_brightness->text();
	mPBrightContrastItem.brightness = Str_B.toFloat();
	Slider_brightness->setValue(int(mPBrightContrastItem.brightness*100.));
	if (checkBox_Preview->isChecked()) emit send_Brightness_Contrast(mPBrightContrastItem, false);
}
void brightnessWindow::setSLiderValueContrast(void){
	QString Str_C = lineEdit_contrast->text();
	mPBrightContrastItem.contrast = Str_C.toFloat();
	Slider_contrast->setValue(int(mPBrightContrastItem.contrast*100.));
	if (checkBox_Preview->isChecked()) emit send_Brightness_Contrast(mPBrightContrastItem, false);
}

void brightnessWindow::brightnesswindowTriggered(void)
{
	emit send_Brightness_Contrast(mPBrightContrastItem, true);
	this->close();
}