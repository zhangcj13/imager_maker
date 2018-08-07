#ifndef CHROMAWINDOW_H
#define CHROMAWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>

#include "structData.h"

class chromaWindow : public QDialog
{
	Q_OBJECT

public:
	chromaWindow(QWidget *parent);
	~chromaWindow();

	QPushButton *pushButton_OK;
	QPushButton *pushButton_Cancel;
	QPushButton *pushButton_intiData;
	QCheckBox *checkBox_Preview;
	QSlider *Slider_H;
	QSlider *Slider_S;
	QSlider *Slider_L;
	QLabel *label_H;
	QLabel *label_S;
	QLabel *label_L;
	QLineEdit *lineEdit_H;
	QLineEdit *lineEdit_S;
	QLineEdit *lineEdit_L;
	QCheckBox *checkBox_color;

	PHLSItem mPHLSItem;
private:
	void retranslateUi(void);
	void setupUi(void);
	void intiData(void);
	private slots:
	void setValueH(int);
	void setValueS(int);
	void setValueL(int);

	void setSLiderValueH(void);
	void setSLiderValueS(void);
	void setSLiderValueL(void);
	void chromaWindowTriggered(void);
signals:
	void PHLSItemChange(PHLSItem, bool);
};

#endif // CHROMAWINDOW_H
