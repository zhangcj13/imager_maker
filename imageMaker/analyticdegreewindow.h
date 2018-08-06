#ifndef ANALYTICDEGREEWINDOW_H
#define ANALYTICDEGREEWINDOW_H

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
#include <QtWidgets/QCheckBox>

class analyticDegreeWindow : public QDialog
{
	Q_OBJECT

public:
	analyticDegreeWindow(int &_w, int &_h, QWidget *parent = 0);
	~analyticDegreeWindow();

public:
	int width;
	int height;
	float ratio;

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
	QCheckBox *checkBox;

	void setupUi(void);

	void retranslateUi(void);



signals:
	void  send_w_h(int, int);
private:
	private slots :
		void refleshDataW(void);
	void refleshDataH(void);
	void analyticDegreeButtonopTriggered(void);
	
};

#endif // ANALYTICDEGREEWINDOW_H
