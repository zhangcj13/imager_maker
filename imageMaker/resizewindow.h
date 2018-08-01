#ifndef RESIZEWINDOW_H
#define RESIZEWINDOW_H

#include <qdialog.h>
#include <qlineedit.h>
#include <QtWidgets/QPushButton>
#include <QDoubleValidator>
//#include "mOpenCV.h"

class resizeWindow : public QDialog
{
	Q_OBJECT

public:
	resizeWindow(QWidget *parent = 0);
	~resizeWindow();

public:
	QPushButton *pushButton;
	QLineEdit *lineEdit;
	//IplImage *reimg;

private:
	void setupUi(void);
	void retranslateUi(void);

	//IplImage* resizeImg(IplImage* imgin, double seedx, double seedy);
signals:
	void  sendSeed(double);
private slots:
    void resizeButtonopTriggered(void);	
};

#endif // RESIZEWINDOW_H
