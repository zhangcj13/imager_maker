#include "mhistgram.h"

mHistGram::mHistGram(QWidget *parent)
	: QWidget(parent),
	sizex(16),
	sizey(10),
	minV(0),
	maxV(255),
	factor(1)
{
	ui.setupUi(this);
}

mHistGram::~mHistGram()
{

}

void mHistGram::setHist(mMatrix<size_t> *_hist)
{
	assert(_hist->getrows() == 3 || _hist->getrows() == 1);
	showMode = _hist->getrows();
	for (int i = 0; i <= _hist->getrows(); i++)
		showColor.push_back(Qt::black);
	maxV = _hist->getcols() - 1;
	this->hist = _hist;
	this->oldhist = _hist;
	this->newhist = new mMatrix < size_t > ;
	this->newhist->creatMatrix(_hist->getrows(), _hist->getcols());
	this->maxValue = hist->mMax();
}

void mHistGram::setshowColor(std::vector<QColor> _showColor)
{
	showColor.clear();
	showColor.insert(showColor.begin(), _showColor.begin(), _showColor.end());
}

void mHistGram::paintEvent(QPaintEvent* event)
{
	QWidget::paintEvent(event);
	QPainter painter(this);
	paintHistGram(&painter);
}

void mHistGram::paintColoredRect(QRectF rect, QColor color, QPainter* painter)
{
	painter->fillRect(rect, QBrush(color));
}
void mHistGram::paintSingleHist(mMatrix<size_t>* _hist, QColor color, QPainter* painter)
{
	float div_x = (float)width() / hist->getcols();
	for (size_t i = 0; i < hist->getcols(); i++)
	{
		float currentHeight = (float)(*_hist)(i) / maxValue * height();
		paintColoredRect(QRectF(i*div_x, height(), div_x, -currentHeight), color, painter);
	}
}

void mHistGram::paintHistGram(QPainter* painter)
{
	paintColoredRect(QRect(0, 0, width() ,height()), Qt::white, painter);
    
	//画y轴的刻度
	float div_y = (float)height() / sizey;
	float div_x = (float)width() / sizex;
	for (int i = 0; i <= sizey; i++)
	{
		painter->drawLine(0, height() - i*div_y, 3, height()- i * div_y);//画刻度线
		//painter->drawText(QPoint(40, 403 - yi*i), QString::number(i));   //画刻度数字
	}
	//画x轴的刻度
	for (int i = 0; i <= sizex; i++)
	{
		painter->drawLine(i*div_x, height(), i*div_x, height() -3);    //画刻度线
	}

	
	if (showMode==hist->getrows())
	{
		mMatrix<size_t> grey(1, hist->getcols());
		int ns = 0;
		for (ns = 0; ns < hist->getrows(); ns++)
		{
			paintSingleHist(&(hist->getrows(ns)), showColor[ns], painter);
			grey = grey + hist->getrows(ns);
		}	
		grey = grey / hist->getrows();
		paintSingleHist(&(grey), showColor[ns], painter);
	}
	else
		//paintSingleHist(&(hist->getrows(showMode)), QColor(255,0,0), painter);
		paintSingleHist(&(hist->getrows(showMode)), showColor[showMode], painter);

}

void mHistGram::setHisShowModel(int data)
{
	assert(data <= hist->getrows());
	showMode = data;
	update();
}

void mHistGram::resetMaxHistgram(float data)
{
	maxV = int(data);
	imgmaker::resetHistorm(*oldhist, newhist, minV, maxV, factor);
	this->hist = newhist;
	update();
}
void mHistGram::resetMinHistgram(float data)
{
	minV = int(data);
	imgmaker::resetHistorm(*oldhist, newhist, minV, maxV, factor);
	this->hist = newhist;
	update();
}
void mHistGram::resetFactorHistgram(float data)
{
	factor = (data - (float)minV) * 2. / ((float)maxV - (float)minV);
	imgmaker::resetHistorm(*oldhist, newhist, minV, maxV, factor);
	this->hist = newhist;
	update();
}



