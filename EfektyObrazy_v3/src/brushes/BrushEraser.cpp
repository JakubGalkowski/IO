#include "BrushEraser.h"

BrushEraser::BrushEraser(): Brush("Eraser")
{
    color = QColor(0,0,0,0);
}

void BrushEraser::move(QPainter & painter, const QPoint & oldpos, const QPoint & newpos)
{
    painter.save();
    painter.setCompositionMode(QPainter::CompositionMode_Clear);
    QPen pen(painter.pen());
    pen.setWidth(this->size);
    pen.setColor(this->color);
    painter.setPen(pen);
    painter.drawLine(oldpos, newpos);
    painter.restore();
}
