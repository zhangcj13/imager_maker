#include "mqabout.h"

#include <QFrame>
#include <QFont>
#include <QPalette>
#include <QDebug>

#define SAFE_FREE(p) {if(p != NULL) {delete p; p = NULL;}}

mQAbout::mQAbout(QWidget *parent)
	: QWidget(parent)
{
	initUiComponent();
}

mQAbout::~mQAbout()
{
	SAFE_FREE(titleLabel);
	SAFE_FREE(authorLabel);
	SAFE_FREE(infoLabel);
	SAFE_FREE(infoTextEdit);
	SAFE_FREE(exitBtn);
}

void mQAbout::initUiComponent(void)
{
	//int label_w = 300, label_h = 20;
	//int text_w = 300, text_h = 120;
	//int btn_w = 80, btn_h = 30;
	int label_w = 500, label_h = 40;
	int text_w = 500, text_h = 190;
	int btn_w = 100, btn_h = 50;

	int btn_x = MQABOUT_WIDGET_WIDTH - btn_w;
	int btn_y = MQABOUT_WIDGET_HEIGHT - btn_h;

	titleLabel = new QLabel(this);
	titleLabel->setText(tr("imageMaker for Windows"));
	titleLabel->setGeometry(20, 10, label_w, label_h);

	QFont titleFont("Microsoft YaHei", 10, QFont::Bold);
	titleLabel->setFont(titleFont);

	authorLabel = new QLabel(this);
	authorLabel->setText(tr("Author: Zhang"));
	authorLabel->setGeometry(100, 30, label_w, label_h);

	infoLabel = new QLabel(this);
	infoLabel->setOpenExternalLinks(true);
	infoLabel->setText(tr("<a href=\"https://github.com/\">"
		"[https://github.com]"));
	infoLabel->setGeometry(40, 50, label_w, label_h);

	QString info;
	info.append("                                     Statement\n");
	info.append("imageMaker is a free and open source project. ");
	info.append("You can according to the published by the free software "
		"if you have any idea or question, please contact me."
		"the email address: zhangcj13@126.com."
		);


	infoTextEdit = new QTextEdit(this);
	infoTextEdit->setText(info);
	infoTextEdit->setReadOnly(1);
	infoTextEdit->setGeometry(15, 80, text_w, text_h);

	QPalette palette;
	palette.setColor(QPalette::Text, Qt::red);
	infoTextEdit->setPalette(palette);
	QFont infoFont("Microsoft YaHei", 8, QFont::Cursive);
	infoTextEdit->setFont(infoFont);

	exitBtn = new QPushButton(this);
	exitBtn->setText(tr("OK"));
	exitBtn->setGeometry(btn_x - 10, btn_y - 5, btn_w, btn_h);
	connect(exitBtn, SIGNAL(clicked(bool)), this, SLOT(exitBtnClicked()));
	
}

void mQAbout::exitBtnClicked(void)
{
	this->close();
}
