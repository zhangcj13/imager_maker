#ifndef MSLIDER_H
#define MSLIDER_H

#include <QWidget>
#include <qpainter.h>
#include <QMouseEvent>
#include "ui_mslider.h"

//template<class _datatype=float>
class mSlider : public QWidget
{
	Q_OBJECT
public:
	mSlider(QWidget *parent = 0);
	~mSlider();
private:
	Ui::mSlider ui;
public:
	void setRange(float min, float max);
	void setSingleStep(float step);
	enum State{ MinHandle, MaxHandle, FactorHandle, None };
	float minValue() const;
	float maxValue() const;
	float minRange() const;
	float maxRange() const;
	float factorRange() const;//DIY
	float factorValue() const;//DIY
	public slots:

	void setLabel(const QString& label);
	void setMaxValue(float val);
	void setMinValue(float val);
	void setFactorValue(float val);//DIY

	void refreshAllValue(float _val1, float _val2, float _val3);//DIY
signals:
	void minValueChanged(float);
	void maxValueChanged(float);
	void factorValueChanged(float);
private:
	float m_min;
	float m_max;
	float m_singleStep;
	float m_minValue;
	float m_maxValue;

	float m_factor;
	float m_factorValue;
	QRect factorHandleRegion;

	QRect minHandleRegion;
	QRect maxHandleRegion;

	State m_state;
	QString m_label;
protected:
	void paintEvent(QPaintEvent* event);
	void paintColoredRect(QRect rect, QColor color, QPainter* painter);
	void paintValueLabel(QPainter* painter);
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void keyPressEvent(QKeyEvent *event);
	void leaveEvent(QEvent* event);
};


#endif // MSLIDER_H
