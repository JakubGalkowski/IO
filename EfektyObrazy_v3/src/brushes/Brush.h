#ifndef BRUSH_H
#define BRUSH_H

#include "../Action.h"
#include <QColor>
#include <QPainter>

class Brush : public Action
{
public:
    Brush(std::string name): Action(name) {};

    int size = 50;
    QColor color = QColor(255,0,0);

    virtual void press(QPainter & painter, const QPoint & pos);
    virtual void move(QPainter & painter, const QPoint & oldpos, const QPoint & newpos);
    virtual void release(QPainter & painter, const QPoint & pos);

};

#endif // BRUSH_H
