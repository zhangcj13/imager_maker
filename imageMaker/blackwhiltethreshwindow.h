#ifndef BLACKWHILTETHRESHWINDOW_H
#define BLACKWHILTETHRESHWINDOW_H

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

#include "mhistgram.h"

class blackwhilteThreshWindow : public QDialog
{
	Q_OBJECT

public:
	blackwhilteThreshWindow(mMatrix<size_t> *_hist, QWidget *parent=0);
	~blackwhilteThreshWindow();
	QPushButton *pushButton_OK;
	QPushButton *pushButton_Cancel;
	QPushButton *pushButton_intiData;
	QPushButton *pushButton_Auto;
	QCheckBox *checkBox_Preview;

	QGroupBox *groupBox;
	QLineEdit *lineEdit_Thresh;
	QSlider *Slider_Thresh;

	mHistGram *histgram;
	QLabel *labelThresh;

	mMatrix<size_t> *hist;
	//QSlider *horizontalSlider;
	std::vector<std::pair<int, QColor>> showMode;

	PColorLevelItem _PColorLevelItem;

	int mThresh;

	void setupUi(void);

	void retranslateUi(void);
signals:
	void ThreshChanged(int, bool);
private:
	private slots :
	void intiData(void);
	void text2slider_refleshData(void);
	void slider2text_refleshData(int);

	void blackwhilteThreshWindowTriggered(void);

	
};

#endif // BLACKWHILTETHRESHWINDOW_H
