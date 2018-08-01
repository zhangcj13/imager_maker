#ifndef PLATEPREDICTWINDOW_H
#define PLATEPREDICTWINDOW_H

#include <qdialog.h>
#include <qlineedit.h>
#include <QtWidgets/QPushButton>
#include <QDoubleValidator>
#include <QGraphicsView>
#include <QLabel>
#include <QTextEdit>

#include "PlatePredict.h"
#include "mPlate_Locate.h"
//#include "mOpenCV.h"

class PlatePredictWindow : public QDialog
{
	Q_OBJECT

public:
	PlatePredictWindow(IplImage *inImg,QWidget *parent = 0);
	~PlatePredictWindow();
	

public:
	//PlatePredict *carImg;

	mPlate_Locate mploc;


	QGraphicsView *graphicsView;
	QGraphicsScene *scene;
	QGraphicsView *graphicsView_2;
	QLabel *label;
	QLabel *label_2;
	QTextEdit *textEdit;
	QPushButton *pushButton;

	QGraphicsScene *scene2;

private:
	void setupUi(void);
	void retranslateUi(void);

signals:
	
	private slots :
		void LocateButtonopTriggered(void);

};

#endif // PLATEPREDICTWINDOW_H
