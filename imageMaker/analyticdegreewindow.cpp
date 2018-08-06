#include "analyticdegreewindow.h"

analyticDegreeWindow::analyticDegreeWindow(int &_w, int &_h, QWidget *parent)
	: QDialog(parent)
{
	this->width = _w;
	this->height = _h;
	this->ratio = (float)_w / _h;
	this->setObjectName(QString::fromLocal8Bit("Í¼Ïñ½âÎö¶È"));
	this->setWindowTitle(QString::fromLocal8Bit("Í¼Ïñ½âÎö¶È"));
	this->resize(485, 300);
	setupUi();
}

analyticDegreeWindow::~analyticDegreeWindow()
{

}

void analyticDegreeWindow::setupUi(void)
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

	checkBox = new QCheckBox(this);
	checkBox->setObjectName(QStringLiteral("checkBox"));
	checkBox->setEnabled(true);
	checkBox->setGeometry(QRect(30, 250, 200, 30));
	checkBox->setAcceptDrops(false);
	checkBox->setAutoFillBackground(false);
	checkBox->setChecked(true);

	connect(checkBox, SIGNAL(clicked()), this, SLOT(refleshDataW(void)));

	pushButton = new QPushButton(this);
	pushButton->setObjectName(QStringLiteral("pushButton"));
	pushButton->setGeometry(QRect(360, 30, 80, 30));
	pushButton_2 = new QPushButton(this);
	pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
	pushButton_2->setGeometry(QRect(360, 80, 80, 30));

	
	

	retranslateUi();
	connect(lineEdit, SIGNAL(textEdited(QString)), this, SLOT(refleshDataW(void)));
	connect(lineEdit_2, SIGNAL(textEdited(QString)), this, SLOT(refleshDataH(void)));
	connect(pushButton, SIGNAL(clicked(bool)), this, SLOT(analyticDegreeButtonopTriggered(void)));
	connect(pushButton_2, SIGNAL(clicked(bool)), this, SLOT(close()));

} // setupUi

void analyticDegreeWindow::retranslateUi(void)
{

	label->setText(QApplication::translate("Dialog", "\347\216\260\345\234\250\347\232\204\345\260\272\345\257\270", 0));
	label_3->setText(QString::number(width) + " * " + QString::number(height));

	groupBox->setTitle(QString::fromLocal8Bit("Í¼Æ¬½âÎö¶È") + "(" + QString::number(width) + " * " + QString::number(height) + ")");
	label_2->setText(QApplication::translate("Dialog", "\345\256\275\345\272\246(W)", 0));
	label_4->setText(QApplication::translate("Dialog", "\351\253\230\345\272\246(H)", 0));

	label_6->setText(QApplication::translate("Dialog", "pixel", 0));
	label_7->setText(QApplication::translate("Dialog", "pixel", 0));
	pushButton->setText(QApplication::translate("Dialog", "\347\241\256\345\256\232", 0));
	pushButton_2->setText(QApplication::translate("Dialog", "\345\217\226\346\266\210", 0));

	checkBox->setText(QString::fromLocal8Bit("¹Ì¶¨¿í¸ß±È"));


} // retranslateUi

void analyticDegreeWindow::refleshDataW(void)
{
	QString Str1 = lineEdit->text();
	
	this->width = Str1.toInt();
	if (checkBox->isChecked())
	{
		this->height = (int)this->width / this->ratio;
		lineEdit_2->setText(QString::number(this->height));
	}
	QString Str2 = lineEdit_2->text();
	groupBox->setTitle(QString::fromLocal8Bit("Í¼Æ¬³ß´ç") + "(" + Str1 + " * " + Str2 + ")");
}
void analyticDegreeWindow::refleshDataH(void)
{
	
	QString Str2 = lineEdit_2->text();

	this->height = Str2.toInt();
	if (checkBox->isChecked())
	{
		this->width = (int)this->height * this->ratio;
		lineEdit->setText(QString::number(this->width));
	}
	QString Str1 = lineEdit->text();
	groupBox->setTitle(QString::fromLocal8Bit("Í¼Æ¬³ß´ç") + "(" + Str1 + " * " + Str2 + ")");
}

void analyticDegreeWindow::analyticDegreeButtonopTriggered(void)
{

	emit send_w_h(width, height);

	this->close();
}







