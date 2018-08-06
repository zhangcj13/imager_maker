#ifndef COLORBALANCEWINDOW_H
#define COLORBALANCEWINDOW_H

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

class colorBalanceWindow : public QDialog
{
	Q_OBJECT

public:
	colorBalanceWindow(QWidget *parent);
	~colorBalanceWindow();

	QPushButton *pushButton_OK;
	QPushButton *pushButton_Cancel;
	QPushButton *pushButton_intiData;
	QCheckBox *checkBox_Preview;
	QSlider *Slider_R;
	QLabel *label;
	QSlider *Slider_G;
	QSlider *Slider_B;
	QLabel *label_2;
	QLabel *label_3;
	QLineEdit *lineEdit_R;
	QLineEdit *lineEdit_G;
	QLineEdit *lineEdit_B;
	QCheckBox *checkBox_synchronous;

	float valueR;
	float valueG;
	float valueB;

private:
	void retranslateUi(void);
	void setupUi(void);
	private slots:
	void setValueR(int);
	void setValueG(int);
	void setValueB(int);

	void setSLiderValueR(void);
	void setSLiderValueG(void);
	void setSLiderValueB(void);
	
};

#endif // COLORBALANCEWINDOW_H
