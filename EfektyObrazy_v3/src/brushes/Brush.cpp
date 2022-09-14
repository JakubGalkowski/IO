#include "Brush.h"

void Brush::press(QPainter & painter, const QPoint & pos)
{
    move(painter, pos, pos);
}

void Brush::move(QPainter & painter, const QPoint & oldpos, const QPoint & newpos)
{
    painter.save();
//    painter.setCompositionMode(QPainter::CompositionMode_Clear);
    QPen pen(painter.pen());
    pen.setWidth(this->size);
    pen.setColor(this->color);
    painter.setPen(pen);
    painter.drawLine(oldpos, newpos);
    painter.restore();
}

void Brush::release(QPainter & /*painter*/, const QPoint & /*pos*/)
{

}
