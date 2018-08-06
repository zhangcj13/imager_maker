#ifndef COLORBANDSWINDOW_H
#define COLORBANDSWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QLabel>

#include "mslider.h"
#include "mslider2.h"
#include "mhistgram.h"

class colorbandsWindow : public QDialog
{
	Q_OBJECT

public:
	colorbandsWindow(mMatrix<size_t> *_hist,QWidget *parent = 0);
	~colorbandsWindow();

	QPushButton *pushButton_OK;
	QPushButton *pushButton_Cancel;
	QPushButton *pushButton_intiData;
	QPushButton *pushButton_Auto;
	QCheckBox *checkBox_Preview;
	QGroupBox *groupBox;
	QComboBox *comboBox_RGB;
	QLineEdit *lineEdit_Min;
	QLineEdit *lineEdit_Factor;
	QLineEdit *lineEdit_Max;
	QTextBrowser *textBrowser_Histogram;
	mSlider* sliderRGB;
	mHistGram *histgram;

	mSlider2* sliderOut;
	QLineEdit *lineEdit_Outmin;
	QLineEdit *lineEdit_Outmax;

	QLabel *labelIn;
	QLabel *labelOut;
	
	mMatrix<size_t> *hist;
	//QSlider *horizontalSlider;
	std::vector<std::pair<int,QColor>> showMode;

	PColorLevelItem _PColorLevelItem;

	void setupUi(void);

	void retranslateUi(void);
signals:
	void PColorLevelItemChange(PColorLevelItem,bool);
private:
	private slots :
		void intiData(void);
		void text2slider_refleshData(void);
	    void slider2text_refleshData(void);
		void Out_text2slider_refleshData(void);
		void Out_slider2text_refleshData(void);
		void setChannel(int);
		void colorbandsWindowTriggered(void);
};

#endif // COLORBANDSWINDOW_H
