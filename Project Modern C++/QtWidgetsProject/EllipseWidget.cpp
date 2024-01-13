#include "EllipseWidget.h"

void EllipseWidget::setColor(const QColor& newColor)
{
	color = newColor;
	update();
}

void EllipseWidget::mousePressEvent(QMouseEvent* event)
{
	Q_UNUSED(event);
	emit clicked();
}