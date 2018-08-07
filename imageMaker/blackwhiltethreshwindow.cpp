#include "blackwhiltethreshwindow.h"

blackwhilteThreshWindow::blackwhilteThreshWindow(mMatrix<size_t> *_hist, QWidget *parent)
	: QDialog(parent),
	mThresh(128)
{
	hist = _hist;
	this->setObjectName(QStringLiteral("Dialog"));
	this->resize(590, 420);
	this->setWindowTitle(QString::fromLocal8Bit("黑白阈值"));
	setupUi();
}

blackwhilteThreshWindow::~blackwhilteThreshWindow()
{

}

void blackwhilteThreshWindow::setupUi(void)
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

	checkBox_Preview = new QCheckBox(this);
	checkBox_Preview->setObjectName(QStringLiteral("checkBox_Preview"));
	checkBox_Preview->setGeometry(QRect(450, 230, 120, 30));
	checkBox_Preview->setChecked(true);

	groupBox = new QGroupBox(this);
	groupBox->setObjectName(QStringLiteral("groupBox"));
	groupBox->setGeometry(QRect(20, 30, 400, 390));


	histgram = new mHistGram(groupBox);
	std::vector<QColor> showColor;
	showColor.push_back(QColor(255, 0, 0)); showColor.push_back(QColor(0, 255, 0));
	showColor.push_back(QColor(0, 0, 255)); showColor.push_back(QColor(30, 30, 30));
	histgram->setHist(hist);
	histgram->setshowColor(showColor);
	histgram->setGeometry(QRect(30, 80, 350, 180));

	lineEdit_Thresh = new QLineEdit(groupBox);
	lineEdit_Thresh->setObjectName(QStringLiteral("lineEdit_Thresh"));
	lineEdit_Thresh->setGeometry(QRect(300, 40, 80, 30));
	QIntValidator *_intValidator = new QIntValidator(this);
	_intValidator->setRange(0, 255);
	lineEdit_Thresh->setValidator(_intValidator);

	Slider_Thresh = new QSlider(groupBox);
	Slider_Thresh->setObjectName(QStringLiteral("Slider_brightness"));
	Slider_Thresh->setGeometry(QRect(30, 280, 350, 20));
	Slider_Thresh->setMinimumSize(QSize(350, 0));
	Slider_Thresh->setOrientation(Qt::Horizontal);


	Slider_Thresh->setMinimum(0);  // 最小值
	Slider_Thresh->setMaximum(255);  // 最大值
	Slider_Thresh->setSingleStep(1);  // 步长


	labelThresh = new QLabel(groupBox);
	labelThresh->setObjectName(QStringLiteral("Thresh"));
	labelThresh->setGeometry(QRect(30, 40, 120, 30));

	connect(lineEdit_Thresh, SIGNAL(textEdited(QString)), this, SLOT(text2slider_refleshData(void)));
	connect(Slider_Thresh, SIGNAL(valueChanged(int)), this, SLOT(slider2text_refleshData(int)));

	connect(pushButton_intiData, SIGNAL(clicked(bool)), this, SLOT(intiData(void)));
	connect(pushButton_OK, SIGNAL(clicked(bool)), this, SLOT(blackwhilteThreshWindowTriggered(void)));
	connect(pushButton_Cancel, SIGNAL(clicked(bool)), this, SLOT(close()));

	retranslateUi();

} // setupUi

void blackwhilteThreshWindow::retranslateUi(void)
{
	lineEdit_Thresh->setText(QString::number(128));
	Slider_Thresh->setValue(128);

	pushButton_OK->setText(QApplication::translate("Dialog", "ok", 0));
	pushButton_Cancel->setText(QApplication::translate("Dialog", "\345\217\226\346\266\210", 0));
	pushButton_intiData->setText(QApplication::translate("Dialog", "\345\210\235\346\234\237\345\200\274", 0));
	
	checkBox_Preview->setText(QApplication::translate("Dialog", "\351\242\204\346\274\224", 0));
	groupBox->setTitle(QApplication::translate("Dialog", "\351\200\232\351\201\223", 0));

} // retranslateUi

void blackwhilteThreshWindow::intiData(void)
{
	lineEdit_Thresh->setText(QString::number(128));
	Slider_Thresh->setValue(128);

	mThresh = 128;

	if (checkBox_Preview->isChecked()) emit ThreshChanged(mThresh, false);
}

void blackwhilteThreshWindow::text2slider_refleshData(void)
{
	QString Str_T = lineEdit_Thresh->text();
	mThresh = Str_T.toFloat();
	Slider_Thresh->setValue(mThresh);
	if (checkBox_Preview->isChecked()) emit ThreshChanged(mThresh, false);
}

void blackwhilteThreshWindow::slider2text_refleshData(int _data)
{
	mThresh = _data;
	lineEdit_Thresh->setText(QString::number(mThresh));
	if (checkBox_Preview->isChecked()) emit ThreshChanged(mThresh, false);
}


void blackwhilteThreshWindow::blackwhilteThreshWindowTriggered(void)
{
	emit ThreshChanged(mThresh, true);
	this->close();
}


