#ifndef MHISTGRAM_H
#define MHISTGRAM_H

#include <QWidget>
#include <qpainter.h>
#include "ui_mhistgram.h"
#include "mMatrix.h"
#include "IMGMAKER_FUNC.h"

using namespace imgmaker;

class mHistGram : public QWidget
{
	Q_OBJECT
private:
	size_t sizex;
	size_t sizey;
	size_t maxV;
	size_t minV;
	float factor;

	size_t maxValue;

	mMatrix<size_t>* hist;
	mMatrix<size_t>* oldhist;
	mMatrix<size_t>* newhist;
	size_t showMode;
	std::vector<QColor> showColor;
	
public:
	mHistGram(QWidget *parent = 0);
	~mHistGram();
	

	void setHist(mMatrix<size_t> *_hist);
	void setshowColor(std::vector<QColor> _showColor);

private:
	Ui::mHistGram ui;
protected:
	void paintEvent(QPaintEvent* event);
	void paintHistGram(QPainter* painter);
	void paintColoredRect(QRectF rect, QColor color, QPainter* painter);
	void paintSingleHist(mMatrix<size_t>* _hist,QColor color, QPainter* painter);
	
	private slots :
	void setHisShowModel(int data);
	void resetMaxHistgram(float data);
	void resetMinHistgram(float data);
	void resetFactorHistgram(float data);
	
};

#endif // MHISTGRAM_H
