#ifndef BRUSHERASER_H
#define BRUSHERASER_H

#include "Brush.h"

class BrushEraser : public Brush
{
public:
    BrushEraser();

    virtual void move(QPainter & painter, const QPoint & oldpos, const QPoint & newpos) override;
};

#endif // BRUSHERASER_H
