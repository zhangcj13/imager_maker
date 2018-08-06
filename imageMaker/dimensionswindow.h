#ifndef DIMENSIONSWINDOW_H
#define DIMENSIONSWINDOW_H


#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include "mqthread.h"

class dimensionsWindow : public QDialog
{
	Q_OBJECT

public:
	dimensionsWindow(int &_w, int &_h, QWidget *parent = 0);
	~dimensionsWindow();

public:
	int width;
	int height;
	int flag;

	QLabel *label;
	QLabel *label_3;
	QGroupBox *groupBox;
	QLabel *label_2;
	QLabel *label_4;
	QLineEdit *lineEdit;
	QLineEdit *lineEdit_2;
	
	QLabel *label_6;
	QLabel *label_7;
	QPushButton *pushButton;
	QPushButton *pushButton_2;

	QGroupBox *groupBox2;
	QRadioButton *radioNone;
	QRadioButton *radioContinuous;
	QRadioButton *radioSymmetric;

	QButtonGroup* radioGroup;

	void setupUi(void);

	void retranslateUi(void);

	

signals:
	void  send_w_h(int,int,int);
private:
	



	private slots :
		void refleshData(void);
		void dimensionButtonopTriggered(void);
		void onRadioGroup(void);
	
	
};

#endif // DIMENSIONSWINDOW_H
