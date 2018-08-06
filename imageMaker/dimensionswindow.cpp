#include "dimensionswindow.h"

dimensionsWindow::dimensionsWindow(int &_w, int &_h, QWidget *parent)
	: QDialog(parent)
{
	this->width = _w;
	this->height = _h;
	this->setObjectName(QString::fromLocal8Bit("Í¼Ïñ³ß´ç"));
	this->setWindowTitle(QString::fromLocal8Bit("Í¼Ïñ³ß´ç"));
	this->resize(485, 415);
	setupUi();
}

dimensionsWindow::~dimensionsWindow()
{

}

void dimensionsWindow::setupUi(void)
{
		
	label = new QLabel(this);
	label->setObjectName(QStringLiteral("label"));
	label->setGeometry(QRect(30, 30, 125, 30));
	label_3 = new QLabel(this);
	label_3->setObjectName(QStringLiteral("label_3"));
	label_3->setGeometry(QRect(160, 30, 200, 30));
	groupBox = new QGroupBox(this);
	groupBox->setObjectName(QStringLiteral("groupBox"));
	groupBox->setGeometry(QRect(30, 80, 320, 150));
	label_2 = new QLabel(groupBox);
	label_2->setObjectName(QStringLiteral("label_2"));
	label_2->setGeometry(QRect(30, 50, 100, 30));
	label_4 = new QLabel(groupBox);
	label_4->setObjectName(QStringLiteral("label_4"));
	label_4->setGeometry(QRect(30, 90, 100, 30));
	lineEdit = new QLineEdit(groupBox);
	lineEdit->setObjectName(QStringLiteral("lineEdit"));
	lineEdit->setGeometry(QRect(140, 50, 90, 30));
	lineEdit_2 = new QLineEdit(groupBox);
	lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
	lineEdit_2->setGeometry(QRect(140, 90, 90, 30));

	lineEdit->setText(QString::number(width));
	lineEdit_2->setText(QString::number(height));


	QIntValidator *_intValidator = new QIntValidator(this);
	_intValidator->setRange(0, 10000);

	lineEdit->setValidator(_intValidator);
	lineEdit_2->setValidator(_intValidator);
	
	label_6 = new QLabel(groupBox);
	label_6->setObjectName(QStringLiteral("label_6"));
	label_6->setGeometry(QRect(235, 49, 65, 30));
	label_7 = new QLabel(groupBox);
	label_7->setObjectName(QStringLiteral("label_7"));
	label_7->setGeometry(QRect(235, 89, 65, 30));

	pushButton = new QPushButton(this);
	pushButton->setObjectName(QStringLiteral("pushButton"));
	pushButton->setGeometry(QRect(360, 30, 80, 30));
	pushButton_2 = new QPushButton(this);
	pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
	pushButton_2->setGeometry(QRect(360, 80, 80, 30));


	groupBox2 = new QGroupBox(this);
	groupBox2->setObjectName(QStringLiteral("groupBox2"));
	groupBox2->setGeometry(QRect(30, 250, 320, 154));
	

	radioNone = new QRadioButton(groupBox2);
	radioNone->setObjectName(QStringLiteral("radioButton"));
	radioNone->setGeometry(QRect(30, 30, 91, 27));
	radioContinuous = new QRadioButton(groupBox2);
	radioContinuous->setObjectName(QStringLiteral("radioButton_2"));
	radioContinuous->setGeometry(QRect(30, 72, 91, 27));
	radioSymmetric = new QRadioButton(groupBox2);
	radioSymmetric->setObjectName(QStringLiteral("radioButton_3"));
	radioSymmetric->setGeometry(QRect(30, 114, 91, 27));
	radioGroup = new QButtonGroup(this);
	radioGroup->addButton(radioNone,0);
	radioGroup->addButton(radioContinuous,1);
	radioGroup->addButton(radioSymmetric,2);

	radioNone->setChecked(true);
	connect(radioNone, SIGNAL(clicked()), this, SLOT(onRadioGroup(void)));
	connect(radioContinuous, SIGNAL(clicked()), this, SLOT(onRadioGroup(void)));
	connect(radioSymmetric, SIGNAL(clicked()), this, SLOT(onRadioGroup(void)));

	retranslateUi();
	connect(lineEdit, SIGNAL(textEdited(QString)), this, SLOT(refleshData(void)));
	connect(lineEdit_2, SIGNAL(textEdited(QString)), this, SLOT(refleshData(void)));
	connect(pushButton, SIGNAL(clicked(bool)), this, SLOT(dimensionButtonopTriggered(void)));
	connect(pushButton_2, SIGNAL(clicked(bool)), this, SLOT(close()));

} // setupUi

void dimensionsWindow::retranslateUi(void)
{
	
	label->setText(QApplication::translate("Dialog", "\347\216\260\345\234\250\347\232\204\345\260\272\345\257\270", 0));
	label_3->setText(QString::number(width) + " * " + QString::number(height));

	groupBox->setTitle(QString::fromLocal8Bit("Í¼Æ¬³ß´ç") + "(" + QString::number(width) + " * " + QString::number(height) + ")");
	label_2->setText(QApplication::translate("Dialog", "\345\256\275\345\272\246(W)", 0));
	label_4->setText(QApplication::translate("Dialog", "\351\253\230\345\272\246(H)", 0));

	label_6->setText(QApplication::translate("Dialog", "pixel", 0));
	label_7->setText(QApplication::translate("Dialog", "pixel", 0));
	pushButton->setText(QApplication::translate("Dialog", "\347\241\256\345\256\232", 0));
	pushButton_2->setText(QApplication::translate("Dialog", "\345\217\226\346\266\210", 0));

	groupBox2->setTitle(QString::fromLocal8Bit("Ìî³äÄ£Ê½"));
	radioNone->setText(QString::fromLocal8Bit("ÎÞ"));
	radioContinuous->setText(QString::fromLocal8Bit("Á¬Ðø"));
	radioSymmetric->setText(QString::fromLocal8Bit("¶Ô³Æ"));


} // retranslateUi

void dimensionsWindow::refleshData(void)
{
	QString Str1 = lineEdit->text();
	QString Str2 = lineEdit_2->text();

	this->width = Str1.toInt();
	this->height = Str2.toInt();

	groupBox->setTitle(QString::fromLocal8Bit("Í¼Æ¬³ß´ç") + "(" + Str1 + " * " + Str2 + ")");
}

void dimensionsWindow::dimensionButtonopTriggered(void)
{
	
	emit send_w_h(width, height, flag);

	this->close();
}
void dimensionsWindow::onRadioGroup(void)
{
	switch (radioGroup->checkedId())
	{

	case 0:
		flag = 0;
		break;
	case 1:
		flag = 1;
		break;
	case 2:
		flag = 2;
		break;
	default:
		flag = 0;
	}
}







