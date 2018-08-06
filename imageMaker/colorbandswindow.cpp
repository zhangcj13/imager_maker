#include "colorbandswindow.h"

colorbandsWindow::colorbandsWindow(mMatrix<size_t> *_hist, QWidget *parent)
	: QDialog(parent),
	_PColorLevelItem(0, 255, 0, 255, 1)
{
	hist = _hist;
	this->setObjectName(QStringLiteral("Dialog"));
	this->resize(590, 420);
	this->setWindowTitle(QString::fromLocal8Bit("色阶补正"));
	setupUi();
}

colorbandsWindow::~colorbandsWindow()
{

}

void colorbandsWindow::setupUi(void)
{
	pushButton_OK = new QPushButton(this);
	pushButton_OK->setObjectName(QStringLiteral("pushButton_OK"));
	pushButton_OK->setGeometry(QRect(450, 30, 120, 30));
	pushButton_Cancel = new QPushButton(this);
	pushButton_Cancel->setObjectName(QStringLiteral("pushButton_Cancel"));
	pushButton_Cancel->setGeometry(QRect(450, 80, 120, 30));
	pushButton_intiData = new QPushButton(this);
	pushButton_intiData->setObjectName(QStringLiteral("pushButton_intiData"));
	pushButton_intiData->setGeometry(QRect(450, 130, 120, 30));
	pushButton_Auto = new QPushButton(this);
	pushButton_Auto->setObjectName(QStringLiteral("pushButton_Auto"));
	pushButton_Auto->setGeometry(QRect(450, 180, 120, 30));

	checkBox_Preview = new QCheckBox(this);
	checkBox_Preview->setObjectName(QStringLiteral("checkBox_Preview"));
	checkBox_Preview->setGeometry(QRect(450, 230, 120, 30));
	checkBox_Preview->setChecked(true);

	groupBox = new QGroupBox(this);
	groupBox->setObjectName(QStringLiteral("groupBox"));
	groupBox->setGeometry(QRect(20, 30, 400, 390));

	comboBox_RGB = new QComboBox(groupBox);
	comboBox_RGB->setObjectName(QStringLiteral("comboBox_RGB"));
	comboBox_RGB->setGeometry(QRect(140, 0, 235, 30));

	sliderRGB = new mSlider(groupBox);
	sliderRGB->setObjectName(QStringLiteral("horizontalSlider22"));
	sliderRGB->setGeometry(QRect(30, 260, 350, 16));

	lineEdit_Min = new QLineEdit(groupBox);
	lineEdit_Min->setObjectName(QStringLiteral("lineEdit_Min"));
	lineEdit_Min->setGeometry(QRect(140, 40, 75, 30));
	lineEdit_Factor = new QLineEdit(groupBox);
	lineEdit_Factor->setObjectName(QStringLiteral("lineEdit_Factor"));
	lineEdit_Factor->setGeometry(QRect(220, 40, 75, 30));
	lineEdit_Max = new QLineEdit(groupBox);
	lineEdit_Max->setObjectName(QStringLiteral("lineEdit_Max"));
	lineEdit_Max->setGeometry(QRect(300, 40, 75, 30));

	QIntValidator *_intValidator = new QIntValidator(this);
	_intValidator->setRange(0, 255);
	lineEdit_Min->setValidator(_intValidator);
	lineEdit_Max->setValidator(_intValidator);
	QDoubleValidator *_DoubleValidator = new QDoubleValidator(this);
	_DoubleValidator->setRange(0., 2.);
	_DoubleValidator->setDecimals(2);
	lineEdit_Factor->setValidator(_DoubleValidator);

	histgram = new mHistGram(groupBox);
	std::vector<QColor> showColor;
	showColor.push_back(QColor(255, 0, 0)); showColor.push_back(QColor(0,255, 0)); 
	showColor.push_back(QColor(0, 0, 255)); showColor.push_back(QColor(30, 30, 30));
	histgram->setHist(hist);
	histgram->setshowColor(showColor);
	histgram->setGeometry(QRect(30, 80, 350, 180));

	lineEdit_Outmin = new QLineEdit(groupBox);
	lineEdit_Outmin->setObjectName(QStringLiteral("lineEdit_Outmin"));
	lineEdit_Outmin->setGeometry(QRect(220, 320, 75, 30));
	lineEdit_Outmax = new QLineEdit(groupBox);
	lineEdit_Outmax->setObjectName(QStringLiteral("lineEdit_Outmax"));
	lineEdit_Outmax->setGeometry(QRect(300, 320, 75, 30));

	labelIn = new QLabel(groupBox);
	labelIn->setObjectName(QStringLiteral("labelOut"));
	labelIn->setGeometry(QRect(30, 40, 120, 30));
	labelOut = new QLabel(groupBox);
	labelOut->setObjectName(QStringLiteral("labelOut"));
	labelOut->setGeometry(QRect(30, 320, 120, 30));

	sliderOut = new mSlider2(groupBox);
	sliderOut->setObjectName(QStringLiteral("Slider_out"));
	sliderOut->setGeometry(QRect(30, 330, 350, 16));

	

	connect(lineEdit_Min, SIGNAL(textEdited(QString)), this, SLOT(text2slider_refleshData(void)));
	connect(lineEdit_Factor, SIGNAL(textEdited(QString)), this, SLOT(text2slider_refleshData(void)));
	connect(lineEdit_Max, SIGNAL(textEdited(QString)), this, SLOT(text2slider_refleshData(void)));

	connect(sliderRGB, SIGNAL(minValueChanged(float)), this, SLOT(slider2text_refleshData(void)));
	connect(sliderRGB, SIGNAL(maxValueChanged(float)), this, SLOT(slider2text_refleshData(void)));
	connect(sliderRGB, SIGNAL(factorValueChanged(float)), this, SLOT(slider2text_refleshData(void)));

	connect(lineEdit_Outmin, SIGNAL(textEdited(QString)), this, SLOT(Out_text2slider_refleshData(void)));
	connect(lineEdit_Outmax, SIGNAL(textEdited(QString)), this, SLOT(Out_text2slider_refleshData(void)));

	connect(sliderOut, SIGNAL(minValueChanged(float)), this, SLOT(Out_slider2text_refleshData(void)));
	connect(sliderOut, SIGNAL(maxValueChanged(float)), this, SLOT(Out_slider2text_refleshData(void)));

	//connect(sliderRGB, SIGNAL(maxValueChanged(float)), histgram, SLOT(resetMaxHistgram(float)));
	//connect(sliderRGB, SIGNAL(minValueChanged(float)), histgram, SLOT(resetMinHistgram(float)));
	//connect(sliderRGB, SIGNAL(factorValueChanged(float)), histgram, SLOT(resetFactorHistgram(float)));

	connect(comboBox_RGB, SIGNAL(currentIndexChanged(int)), histgram, SLOT(setHisShowModel(int)));

	connect(comboBox_RGB, SIGNAL(currentIndexChanged(int)), this, SLOT(setChannel(int)));


	connect(pushButton_intiData, SIGNAL(clicked(bool)), this, SLOT(intiData(void)));
	connect(pushButton_OK, SIGNAL(clicked(bool)), this, SLOT(colorbandsWindowTriggered(void)));
	connect(pushButton_Cancel, SIGNAL(clicked(bool)), this, SLOT(close()));

	retranslateUi();

} // setupUi

void colorbandsWindow::retranslateUi(void)
{
	lineEdit_Min->setText(QString::number(0));
	lineEdit_Max->setText(QString::number(255));
	lineEdit_Factor->setText("1.00");

	lineEdit_Outmin->setText(QString::number(0));
	lineEdit_Outmax->setText(QString::number(255));

	pushButton_OK->setText(QApplication::translate("Dialog", "ok", 0));
	pushButton_Cancel->setText(QApplication::translate("Dialog", "\345\217\226\346\266\210", 0));
	pushButton_intiData->setText(QApplication::translate("Dialog", "\345\210\235\346\234\237\345\200\274", 0));
	pushButton_Auto->setText(QApplication::translate("Dialog", "\350\207\252\345\212\250\350\260\203\346\255\243", 0));
	checkBox_Preview->setText(QApplication::translate("Dialog", "\351\242\204\346\274\224", 0));
	groupBox->setTitle(QApplication::translate("Dialog", "\351\200\232\351\201\223", 0));
	comboBox_RGB->clear();
	comboBox_RGB->insertItems(0, QStringList()
		<< QApplication::translate("Dialog", "R", 0)
		<< QApplication::translate("Dialog", "G", 0)
		<< QApplication::translate("Dialog", "B", 0)
		<< QApplication::translate("Dialog", "RGB", 0)
		);
	comboBox_RGB->setCurrentIndex(3);

	labelIn->setText(QString::fromLocal8Bit("输入水准:"));
	labelOut->setText(QString::fromLocal8Bit("输出水准:"));

} // retranslateUi

void colorbandsWindow::intiData(void)
{
	lineEdit_Min->setText(QString::number(0));
	lineEdit_Max->setText(QString::number(255));
	lineEdit_Factor->setText(QString::number(1.00, 'f', 2));
	sliderRGB->refreshAllValue(0., 255., 128.0);

	lineEdit_Outmin->setText(QString::number(0));
	lineEdit_Outmax->setText(QString::number(255));
	sliderOut->refreshAllValue(0., 255.);

	_PColorLevelItem.Shadow = 0;
	_PColorLevelItem.Highlight = 255;
	_PColorLevelItem.Midtones = 1.0;
	_PColorLevelItem.OutShadow = 0;
	_PColorLevelItem.OutHighlight = 255;

	if (checkBox_Preview->isChecked()) emit PColorLevelItemChange(_PColorLevelItem, false);
}

void colorbandsWindow::text2slider_refleshData(void)
{
	QString Str_max = lineEdit_Max->text();
	QString Str_min = lineEdit_Min->text();
	QString Str_Factor = lineEdit_Factor->text();

	float maxValue = Str_max.toFloat();
	float minValue = Str_min.toFloat();
	float factor = Str_Factor.toFloat();

	float factorValue = (maxValue - minValue)/2.*factor + minValue;
	sliderRGB->refreshAllValue(minValue, maxValue, factorValue);

	_PColorLevelItem.Shadow = minValue;
	_PColorLevelItem.Highlight = maxValue;
	_PColorLevelItem.Midtones = factor;
	if (checkBox_Preview->isChecked()) emit PColorLevelItemChange(_PColorLevelItem, false);
}

void colorbandsWindow::slider2text_refleshData(void)
{
	float minValue = sliderRGB->minValue();
	float  maxValue = sliderRGB->maxValue();
	float factorValue = sliderRGB->factorValue();

	double factor =  (factorValue - minValue) * 2 / (maxValue - minValue);

	lineEdit_Min->setText(QString::number((int)minValue));
	lineEdit_Max->setText(QString::number((int)maxValue));
	lineEdit_Factor->setText(QString::number(factor,'f',2));

	_PColorLevelItem.Shadow = minValue;
	_PColorLevelItem.Highlight = maxValue;
	_PColorLevelItem.Midtones = factor;
	if (checkBox_Preview->isChecked()) emit PColorLevelItemChange(_PColorLevelItem, false);
}

void colorbandsWindow::Out_text2slider_refleshData(void)
{
	QString Str_max = lineEdit_Outmin->text();
	QString Str_min = lineEdit_Outmax->text();

	float maxValue = Str_max.toFloat();
	float minValue = Str_min.toFloat();

	sliderOut->refreshAllValue(minValue, maxValue);

	_PColorLevelItem.OutShadow = minValue;
	_PColorLevelItem.OutHighlight = maxValue;
	if (checkBox_Preview->isChecked()) emit PColorLevelItemChange(_PColorLevelItem, false);
}

void colorbandsWindow::Out_slider2text_refleshData(void)
{
	float minValue = sliderOut->minValue();
	float  maxValue = sliderOut->maxValue();


	lineEdit_Outmin->setText(QString::number((int)minValue));
	lineEdit_Outmax->setText(QString::number((int)maxValue));

	_PColorLevelItem.OutShadow = minValue;
	_PColorLevelItem.OutHighlight = maxValue;
	if (checkBox_Preview->isChecked()) emit PColorLevelItemChange(_PColorLevelItem, false);
}

void colorbandsWindow::setChannel(int _data)
{
	_PColorLevelItem.numchannel = _data;

	if (checkBox_Preview->isChecked()) emit PColorLevelItemChange(_PColorLevelItem, false);
}

void colorbandsWindow::colorbandsWindowTriggered(void)
{
	emit PColorLevelItemChange(_PColorLevelItem, true);
	this->close();
}


