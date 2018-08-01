#ifndef TILTWINDOW_H
#define TILTWINDOW_H

#include <qdialog.h>
#include <qlineedit.h>
#include <QtWidgets/QPushButton>
#include <QDoubleValidator>
//#include "mOpenCV.h"

	class tiltWindow : public QDialog
	{
		Q_OBJECT

	public:
		tiltWindow(QWidget *parent = 0);
		~tiltWindow();

	public:
		QPushButton *pushButton;
		QLineEdit *lineEditX;
		QLineEdit *lineEditY;
		//IplImage *reimg;

	private:
		void setupUi(void);
		void retranslateUi(void);

	signals:
		void  sendTiltAngle(double, double);
		private slots:
		void tiltButtonopTriggered(void);
	};

#endif // TILTWINDOW_H
