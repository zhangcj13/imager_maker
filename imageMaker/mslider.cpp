#include "mslider.h"

inline float getValidValue(float val, float min, float max)
{
	float tmp = std::max(val, min);
	return std::min(tmp, max);
}

mSlider::~mSlider()
{

}

mSlider::mSlider(QWidget* parent)
	: QWidget(parent)
	, m_min(0.0f)
	, m_max(255.0f)
	, m_singleStep(1.f)
	, m_minValue(0.0f)
	, m_maxValue(255.0f)
	, m_factorValue(127.0f)
	, m_state(None)
{
	setFixedHeight(50);
	setFocusPolicy(Qt::StrongFocus);
}

void mSlider::paintEvent(QPaintEvent* event)
{
	QWidget::paintEvent(event);
	QPainter painter(this);
	paintValueLabel(&painter);
}

void mSlider::paintColoredRect(QRect rect, QColor color, QPainter* painter)
{
	painter->fillRect(rect, QBrush(color));
}

void mSlider::paintValueLabel(QPainter* painter)
{
	/*painter->setBrush(Qt::NoBrush);
	painter->setPen(Qt::black);
	painter->setFont(QFont("Arial", 12));

	QString minValueString = QString::number(m_minValue, 'f', 3);
	QString maxValueString = QString::number(m_maxValue, 'f', 3);

	QString factorValueString = QString::number(m_factorValue, 'f', 3);//DIY

	QFontMetrics metrics = painter->fontMetrics();
	int mintextWidth = metrics.width(minValueString);
	int maxtextWidth = metrics.width(maxValueString);
	int factortectWidth = metrics.width(factorValueString);//DIY
	int textHeight = metrics.height();
	//---- paint text
	painter->drawText(QRectF(2, 4, mintextWidth, textHeight), minValueString);
	painter->drawText(QRectF(width() - maxtextWidth - 2, 4, maxtextWidth, textHeight), maxValueString);

	//----- paint label
	painter->setFont(QFont("Arial", 12));
	metrics = painter->fontMetrics();
	int labelWidth = metrics.width(m_label);
	int labelHeight = metrics.height();

	QRectF textRect = QRectF((width() / 2 - labelWidth / 2), 0, labelWidth, labelHeight);
	painter->drawText(textRect, m_label);*/

	int minPos = (m_minValue - m_min) * width() / (m_max - m_min);
	int maxPos = (m_maxValue - m_min) * width() / (m_max - m_min);
	int facrorPos = (m_factorValue - m_min) * width() / (m_max - m_min);

	if (minPos <= 4)
	{
		minPos = 4;
	}
	else if (minPos >= width() - 8)
	{
		minPos = width() - 8;
	}
	else{}

	if (maxPos <= 4)
	{
		maxPos = 4;
	}
	else if (maxPos >= width() - 8)
	{
		maxPos = width() - 8;
	}
	else{}

	if (facrorPos <4)
	{
		facrorPos = 4;
	}
	else if (facrorPos >= width() - 8)
	{
		facrorPos = width() - 8;
	}
	else{}
	//----- paint groove
	paintColoredRect(QRect(4, 34, width() - 8, 6), Qt::gray, painter);
	paintColoredRect(QRect(minPos + 4, 34, maxPos - minPos, 6), QColor(51, 153, 155), painter);
	//----- handle
	minHandleRegion = QRect(minPos, 30, 8, 16);
	maxHandleRegion = QRect(maxPos, 30, 8, 16);
	factorHandleRegion = QRect(facrorPos, 30, 8, 16);//DIY
	//-----paint Handle
	QColor minColor = (m_state == MinHandle) ? QColor(255, 0, 0) : QColor(0, 0, 0);
	QColor maxColor = (m_state == MaxHandle) ? QColor(255, 0, 0) : QColor(200, 200, 200);
	QColor factorColor = (m_state == FactorHandle) ? QColor(255, 0, 0) : QColor(100, 100, 100);
	paintColoredRect(minHandleRegion, minColor, painter);
	paintColoredRect(maxHandleRegion, maxColor, painter);
	paintColoredRect(factorHandleRegion, factorColor, painter);//DIY
}

void mSlider::setRange(float min, float max)
{
	m_min = min;
	m_max = max;
	if (minValue() < m_min)
		setMinValue(m_min);
	if (maxValue() > m_max)
		setMaxValue(m_max);
}

void mSlider::setSingleStep(float step)
{
	m_singleStep = step;
}

float mSlider::minValue() const
{
	return m_minValue;
}

void mSlider::setMinValue(float val)
{
	if (fabs(m_minValue - val) > 0.0001)
	{
		float factor = (m_factorValue - m_minValue) * 2 / (m_maxValue - m_minValue);
		m_minValue = val;
		m_factorValue = (m_maxValue - m_minValue) / 2.*factor + m_minValue;
		emit minValueChanged(val);
	}
}

float mSlider::maxValue() const
{
	return m_maxValue;
}

void mSlider::setMaxValue(float val)
{
	if (fabs(m_maxValue - val) > 0.0001)
	{
		float factor = (m_factorValue - m_minValue) * 2 / (m_maxValue - m_minValue);
		m_maxValue = val;
		m_factorValue = (m_maxValue - m_minValue) / 2.*factor + m_minValue;
		emit maxValueChanged(val);
	}
}

float mSlider::factorValue() const
{
	return m_factorValue;
}

void mSlider::setFactorValue(float val)
{
	if (fabs(m_factorValue - val) > 0.0001)
	{
		m_factorValue = val;
		emit factorValueChanged(val);
	}
}

void mSlider::setLabel(const QString& label)
{
	m_label = label;
	update();
}

void mSlider::leaveEvent(QEvent* event)
{
	QWidget::leaveEvent(event);
	m_state = None;
	update();
}

float mSlider::minRange() const
{
	return m_min;
}

float mSlider::maxRange() const
{
	return m_max;
}

void mSlider::mousePressEvent(QMouseEvent* event)
{
	if (minHandleRegion.contains(event->pos()))
	{
		m_state = MinHandle;
	}
	else if (maxHandleRegion.contains(event->pos()))
	{
		m_state = MaxHandle;
	}
	else if (factorHandleRegion.contains(event->pos()))
	{
		m_state = FactorHandle;
	}
	else
	{
		m_state = None;
	}
	/*if (fabs(minValue() - maxValue()) < 0.001)
	{
		if (fabs(minValue() - m_min) < 0.001)
		{
			m_state = MaxHandle;
		}
		else if (fabs(minValue() - m_max) < 0.001)
		{
			m_state = MinHandle;
		}
		else{}
	}*/
	if (fabs(minValue() - maxValue()) < 0.001)
	{
		if (fabs(minValue() - m_min) < 0.001)
		{
			m_state = MaxHandle;
		}
		else if (fabs(minValue() - m_max) < 0.001)
		{
			m_state = MinHandle;
		}
		else{}
	}
	else if ((fabs(minValue() - factorValue()) < 0.001) || (fabs(maxValue() - factorValue()) < 0.001))
	{
		m_state = FactorHandle;
	}
	update();
}

void mSlider::mouseMoveEvent(QMouseEvent* event)
{
	if (event->buttons() & Qt::LeftButton)
	{
		float move = event->x() * (m_max - m_min) * 1.0 / width() + m_min;
		switch (m_state){
		case MinHandle:
		{
			float val = getValidValue(move, m_min, factorValue());
			setMinValue(val);
			break;
		}
		case MaxHandle:
		{
			float val = getValidValue(move, factorValue(), m_max);
			setMaxValue(val);
			break;
		}
		case FactorHandle:
		{
			float val = getValidValue(move, minValue(), maxValue());
			setFactorValue(val);
			break;
		}
		case None:default: break;
		}
	}
	update();
}

void mSlider::keyPressEvent(QKeyEvent *event)
{
	QWidget::keyPressEvent(event);
	float val;
	if (event->key() == Qt::Key_Left)
	{
		switch (m_state)
		{
		case MinHandle:
		{
			val = getValidValue(minValue() - m_singleStep, m_min, maxValue());
			setMinValue(val);
			break; 
		}
		case MaxHandle:
		{
			val = getValidValue(maxValue() - m_singleStep, minValue(), m_max);
			setMaxValue(val);
			break;
		}
		case FactorHandle:
		{
			val = getValidValue(factorValue() - m_singleStep, minValue(), maxValue());
			setFactorValue(val);
			break; 
		}
		}
	}
	else if (event->key() == Qt::Key_Right)
	{
		switch (m_state)
		{
		case MinHandle:
		{
			val = getValidValue(minValue() + m_singleStep, m_min, maxValue());
			setMinValue(val);
			break; 
		}
		case MaxHandle:
		{
			val = getValidValue(maxValue() + m_singleStep, minValue(), m_max);
			setMaxValue(val);
			break;
		}
		case FactorHandle:
		{
			val = getValidValue(factorValue() + m_singleStep, factorValue(), m_factor);
			setFactorValue(val);
			break;
		}
		}
	}
	update();
}

void mSlider::refreshAllValue(float _val1, float _val2, float _val3)
{
	setMinValue(_val1);
	setMaxValue(_val2);
	setFactorValue(_val3);
	update();
}

