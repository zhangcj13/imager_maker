#include "mslider2.h"
inline float getValidValue(float val, float min, float max)
{
	float tmp = std::max(val, min);
	return std::min(tmp, max);
}
//---------------------------------------------------------------------------
mSlider2::~mSlider2()
{

}

mSlider2::mSlider2(QWidget* parent)
	: QWidget(parent)
	, m_min(0.0f)
	, m_max(255.0f)
	, m_singleStep(1.f)
	, m_minValue(0.0f)
	, m_maxValue(255.0f)
	, m_state(None)
{
	setFixedHeight(50);
	setFocusPolicy(Qt::StrongFocus);
}

void mSlider2::paintEvent(QPaintEvent* event)
{
	QWidget::paintEvent(event);
	QPainter painter(this);
	paintValueLabel(&painter);
}

void mSlider2::paintColoredRect(QRect rect, QColor color, QPainter* painter)
{
	painter->fillRect(rect, QBrush(color));
}

void mSlider2::paintValueLabel(QPainter* painter)
{

	int minPos = (m_minValue - m_min) * width() / (m_max - m_min);
	int maxPos = (m_maxValue - m_min) * width() / (m_max - m_min);

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

	//----- paint groove
	paintColoredRect(QRect(4, 34, width() - 8, 6), Qt::gray, painter);
	paintColoredRect(QRect(minPos + 4, 34, maxPos - minPos, 6), QColor(128, 90, 155), painter);
	//----- handle
	minHandleRegion = QRect(minPos, 30, 8, 16);
	maxHandleRegion = QRect(maxPos, 30, 8, 16);
	//-----paint Handle
	QColor minColor = (m_state == MinHandle) ? QColor(255, 0, 0) : QColor(0, 0, 0);
	QColor maxColor = (m_state == MaxHandle) ? QColor(255, 0, 0) : QColor(200, 200, 200);
	paintColoredRect(minHandleRegion, minColor, painter);
	paintColoredRect(maxHandleRegion, maxColor, painter);
}

void mSlider2::setRange(float min, float max)
{
	m_min = min;
	m_max = max;
	if (minValue() < m_min)
		setMinValue(m_min);
	if (maxValue() > m_max)
		setMaxValue(m_max);
}

void mSlider2::setSingleStep(float step)
{
	m_singleStep = step;
}

float mSlider2::minValue() const
{
	return m_minValue;
}

void mSlider2::setMinValue(float val)
{
	if (fabs(m_minValue - val) > 0.0001)
	{
		m_minValue = val;
		emit minValueChanged(val);
	}
}

float mSlider2::maxValue() const
{
	return m_maxValue;
}

void mSlider2::setMaxValue(float val)
{
	if (fabs(m_maxValue - val) > 0.0001)
	{
		m_maxValue = val;
		emit maxValueChanged(val);
	}
}

void mSlider2::setLabel(const QString& label)
{
	m_label = label;
	update();
}

void mSlider2::leaveEvent(QEvent* event)
{
	QWidget::leaveEvent(event);
	m_state = None;
	update();
}

float mSlider2::minRange() const
{
	return m_min;
}

float mSlider2::maxRange() const
{
	return m_max;
}

void mSlider2::mousePressEvent(QMouseEvent* event)
{
	if (minHandleRegion.contains(event->pos()))
	{
		m_state = MinHandle;
	}
	else if (maxHandleRegion.contains(event->pos()))
	{
		m_state = MaxHandle;
	}
	else
	{
		m_state = None;
	}
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
	update();
}

void mSlider2::mouseMoveEvent(QMouseEvent* event)
{
	if (event->buttons() & Qt::LeftButton)
	{
		float move = event->x() * (m_max - m_min) * 1.0 / width() + m_min;
		switch (m_state){
		case MinHandle:
		{
			float val = getValidValue(move, m_min, maxValue());
			setMinValue(val);
			break;
		}
		case MaxHandle:
		{
			float val = getValidValue(move, minValue(), m_max);
			setMaxValue(val);
			break;
		}
		case None:default: break;
		}
	}
	update();
}

void mSlider2::keyPressEvent(QKeyEvent *event)
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
		}
	}
	update();
}

void mSlider2::refreshAllValue(float _val1, float _val2)
{
	setMinValue(_val1);
	setMaxValue(_val2);
	update();
}
