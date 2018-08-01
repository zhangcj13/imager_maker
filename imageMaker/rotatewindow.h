#ifndef ROTATEWINDOW_H
#define ROTATEWINDOW_H

#include <qdialog.h>
#include <qlineedit.h>
#include <QtWidgets/QPushButton>
#include <QDoubleValidator>
//#include "mOpenCV.h"

class rotateWindow : public QDialog
{
	Q_OBJECT

public:
	rotateWindow(QWidget *parent = 0);
	~rotateWindow();

public:
	QPushButton *pushButton;
	QLineEdit *lineEdit;
	//IplImage *reimg;

private:
	void setupUi(void);
	void retranslateUi(void);

signals:
	void  sendAngle(double);
private slots:
	void rotateButtonopTriggered(void);
};

#endif // ROTATEWINDOW_H
