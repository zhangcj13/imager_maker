#ifndef BRIGHTNESSWINDOW_H
#define BRIGHTNESSWINDOW_H
#include "structData.h"

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

class brightnessWindow : public QDialog
{
	Q_OBJECT

public:
	brightnessWindow(QWidget *parent=0);
	~brightnessWindow();

	QPushButton *pushButton_OK;
	QPushButton *pushButton_Cancel;
	QPushButton *pushButton_intiData;
	QCheckBox *checkBox_Preview;
	QSlider *Slider_brightness;
	QLabel *label_brightness;
	QSlider *Slider_contrast;
	QLabel *label_contrast;
	QLineEdit *lineEdit_brightness;
	QLineEdit *lineEdit_contrast;
	QCheckBox *checkBox_linear;

private:
	PBrightContrastItem mPBrightContrastItem;

	void setupUi(void);
	void retranslateUi(void);
	private slots:
	void setValueBrightness(int);
	void setValueContrast(int);
	void setSLiderValueBrightness(void);
	void setSLiderValueContrast(void);
	void intiData(void);
	void brightnesswindowTriggered(void);
signals:
	void send_Brightness_Contrast(PBrightContrastItem,bool);
	
};

#endif // BRIGHTNESSWINDOW_H
