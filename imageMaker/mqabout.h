#ifndef MQABOUT_H
#define MQABOUT_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>

#define MQABOUT_WIDGET_WIDTH     320*2
#define MQABOUT_WIDGET_HEIGHT    240*2

class mQAbout : public QWidget
{
	Q_OBJECT

public:
	mQAbout(QWidget *parent=0);
	~mQAbout();
private:
	QPushButton *exitBtn;
	QLabel *infoLabel;
	QLabel *titleLabel;
	QLabel *authorLabel;
	QTextEdit *infoTextEdit;
	void initUiComponent(void);

public slots:
	void exitBtnClicked(void);
};

#endif // MQABOUT_H
