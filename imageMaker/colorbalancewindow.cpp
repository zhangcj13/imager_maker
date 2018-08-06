#include "colorbalancewindow.h"

colorBalanceWindow::colorBalanceWindow(QWidget *parent)
	: QDialog(parent)
{
	this->setObjectName(QStringLiteral("Dialog"));
	this->resize(500, 350);
	this->setWindowTitle(QString::fromLocal8Bit("色彩平衡"));
	setupUi();
}

colorBalanceWindow::~colorBalanceWindow()
{

}

void colorBalanceWindow::setupUi(void)
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

	Slider_R = new QSlider(this);
	Slider_R->setObjectName(QStringLiteral("Slider_R"));
	Slider_R->setGeometry(QRect(50, 80, 270, 16));
	Slider_R->setMinimumSize(QSize(270, 0));
	Slider_R->setOrientation(Qt::Horizontal);
	Slider_G = new QSlider(this);
	Slider_G->setObjectName(QStringLiteral("Slider_G"));
	Slider_G->setGeometry(QRect(50, 140, 270, 16));
	Slider_G->setMinimumSize(QSize(270, 0));
	Slider_G->setOrientation(Qt::Horizontal);
	Slider_B = new QSlider(this);
	Slider_B->setObjectName(QStringLiteral("Slider_B"));
	Slider_B->setGeometry(QRect(50, 200, 270, 16));
	Slider_B->setMinimumSize(QSize(270, 0));
	Slider_B->setOrientation(Qt::Horizontal);

	Slider_R->setMinimum(-100);  // 最小值
	Slider_R->setMaximum(100);  // 最大值
	Slider_R->setSingleStep(1);  // 步长
	Slider_G->setMinimum(-100);  // 最小值
	Slider_G->setMaximum(100);  // 最大值
	Slider_G->setSingleStep(1);  // 步长
	Slider_B->setMinimum(-100);  // 最小值
	Slider_B->setMaximum(100);  // 最大值
	Slider_B->setSingleStep(1);  // 步长

	label = new QLabel(this);
	label->setObjectName(QStringLiteral("label"));
	label->setGeometry(QRect(50, 40, 60, 30));
	label_2 = new QLabel(this);
	label_2->setObjectName(QStringLiteral("label_2"));
	label_2->setGeometry(QRect(50, 100, 60, 30));
	label_3 = new QLabel(this);
	label_3->setObjectName(QStringLiteral("label_3"));
	label_3->setGeometry(QRect(50, 160, 60, 30));

	lineEdit_R = new QLineEdit(this);
	lineEdit_R->setObjectName(QStringLiteral("lineEdit_R"));
	lineEdit_R->setGeometry(QRect(220, 40, 100, 30));
	lineEdit_G = new QLineEdit(this);
	lineEdit_G->setObjectName(QStringLiteral("lineEdit_G"));
	lineEdit_G->setGeometry(QRect(220, 100, 100, 30));
	lineEdit_B = new QLineEdit(this);
	lineEdit_B->setObjectName(QStringLiteral("lineEdit_B"));
	lineEdit_B->setGeometry(QRect(220, 160, 100, 30));

	QDoubleValidator *_DoubleValidator = new QDoubleValidator(this);
	_DoubleValidator->setRange(0.5, 2.);
	_DoubleValidator->setDecimals(2);
	lineEdit_R->setValidator(_DoubleValidator);
	lineEdit_G->setValidator(_DoubleValidator);
	lineEdit_B->setValidator(_DoubleValidator);

	checkBox_synchronous = new QCheckBox(this);
	checkBox_synchronous->setObjectName(QStringLiteral("checkBox_synchronous"));
	checkBox_synchronous->setGeometry(QRect(50, 250, 120, 30));

	retranslateUi();

	connect(Slider_R, SIGNAL(valueChanged(int)), this, SLOT(setValueR(int)));
	connect(Slider_G, SIGNAL(valueChanged(int)), this, SLOT(setValueG(int)));
	connect(Slider_B, SIGNAL(valueChanged(int)), this, SLOT(setValueB(int)));

	connect(lineEdit_R, SIGNAL(textEdited(QString)), this, SLOT(setSLiderValueR(void)));
	connect(lineEdit_G, SIGNAL(textEdited(QString)), this, SLOT(setSLiderValueG(void)));
	connect(lineEdit_B, SIGNAL(textEdited(QString)), this, SLOT(setSLiderValueB(void)));
} // setupUi

void colorBalanceWindow::retranslateUi(void)
{
	pushButton_OK->setText(QApplication::translate("this", "ok", 0));
	pushButton_Cancel->setText(QApplication::translate("this", "\345\217\226\346\266\210", 0));
	pushButton_intiData->setText(QApplication::translate("this", "\345\210\235\346\234\237\345\200\274", 0));
	checkBox_Preview->setText(QApplication::translate("this", "\351\242\204\346\274\224", 0));
	label->setText(QApplication::translate("this", "R", 0));
	label_2->setText(QApplication::translate("this", "G", 0));
	label_3->setText(QApplication::translate("this", "B", 0));
	checkBox_synchronous->setText(QApplication::translate("this", "\345\220\214\346\255\245", 0));

	lineEdit_R->setText(QString::number(1));
	lineEdit_G->setText(QString::number(1));
	lineEdit_B->setText(QString::number(1));
} // retranslateUi

void colorBalanceWindow::setValueR(int _data)
{
	valueR = pow(2,(float)_data / 100);
	lineEdit_R->setText(QString::number(valueR, 'f', 2));
	if (checkBox_synchronous->isChecked())
	{
		valueG = valueR;
		valueB = valueR;
		lineEdit_G->setText(QString::number(valueG, 'f', 2));
		lineEdit_B->setText(QString::number(valueB, 'f', 2));
		Slider_G->setValue(_data);
		Slider_B->setValue(_data);
	}
}
void colorBalanceWindow::setValueG(int _data)
{
	valueG = pow(2, (float)_data / 100);
	lineEdit_G->setText(QString::number(valueG, 'f', 2));
	if (checkBox_synchronous->isChecked())
	{
		valueR = valueG;
		valueB = valueG;
		lineEdit_R->setText(QString::number(valueR, 'f', 2));		
		lineEdit_B->setText(QString::number(valueB, 'f', 2));
		Slider_R->setValue(_data);
		Slider_B->setValue(_data);

	}
}
void colorBalanceWindow::setValueB(int _data)
{
	valueB = pow(2, (float)_data / 100);
	lineEdit_B->setText(QString::number(valueB, 'f', 2));
	if (checkBox_synchronous->isChecked())
	{
		valueR = valueB;
		valueG = valueB;
		lineEdit_R->setText(QString::number(valueR, 'f', 2));
		lineEdit_G->setText(QString::number(valueG, 'f', 2));
		Slider_R->setValue(_data);
		Slider_G->setValue(_data);


	}
}

void colorBalanceWindow::setSLiderValueR(void)
{
	QString Str_R = lineEdit_R->text();
	valueR = Str_R.toFloat();
	int sliderValue = int(log2(valueR)*100.);
	Slider_R->setValue(sliderValue);
	if (checkBox_synchronous->isChecked())
	{
		valueG = valueR;
		valueB = valueR;
		Slider_G->setValue(sliderValue);
		Slider_B->setValue(sliderValue);
		lineEdit_G->setText(QString::number(valueG, 'f', 2));
		lineEdit_B->setText(QString::number(valueB, 'f', 2));		
	}
}
void colorBalanceWindow::setSLiderValueG(void)
{
	QString Str_G = lineEdit_G->text();
	valueG = Str_G.toFloat();
	int sliderValue = int(log2(valueG)*100.);
	Slider_G->setValue(sliderValue);
	if (checkBox_synchronous->isChecked())
	{
		valueR = valueG;
		valueB = valueG;
		Slider_R->setValue(sliderValue);
		Slider_B->setValue(sliderValue);
		lineEdit_R->setText(QString::number(valueR, 'f', 2));
		lineEdit_B->setText(QString::number(valueB, 'f', 2));
	}
}
void colorBalanceWindow::setSLiderValueB(void)
{
	QString Str_B = lineEdit_B->text();
	valueB = Str_B.toFloat();
	int sliderValue = int(log2(valueB)*100.);
	Slider_B->setValue(sliderValue);
	if (checkBox_synchronous->isChecked())
	{
		valueG = valueB;
		valueR = valueB;
		Slider_G->setValue(sliderValue);
		Slider_R->setValue(sliderValue);
		lineEdit_G->setText(QString::number(valueG, 'f', 2));
		lineEdit_R->setText(QString::number(valueR, 'f', 2));
	}
}


