#include "PaintArea.h"

#include <QPainter>
#include <QMouseEvent>
#include "History.h"
#include "brushes/BrushRegistry.h"
#include "MainWindow.h"

PaintArea::PaintArea(QWidget *parent)
    : QWidget{parent}
{

}

QPoint lastPos = QPoint(-1, -1);
QImage lastImg;

void PaintArea::mousePressEvent(QMouseEvent *event)
{
    if (BrushRegistry::get().current == nullptr) return;
    lastImg = m_img;

    Brush * br = BrushRegistry::get().current->brush;

    float scale = (float)m_img.width() / (float)this->width();
    QPoint ppos = event->position().toPoint() * scale;

    if (event->button() == Qt::LeftButton)
    {
        QPainter painter(&m_img);
        br->press(painter, ppos);

        update();

        lastPos = ppos;
    }
}

void PaintArea::mouseReleaseEvent(QMouseEvent *event)
{
    if (BrushRegistry::get().current == nullptr) return;

    Brush * br = BrushRegistry::get().current->brush;

    History::get().add(br, lastImg);
    QWidget * org = parentWidget()->parentWidget()->parentWidget();
    MainWindow * mw = dynamic_cast<MainWindow*>(org);

    if (mw) mw->updateHistoryView();


    float scale = (float)m_img.width() / (float)this->width();
    QPoint ppos = event->pos() * scale;


    if (event->button() == Qt::LeftButton && lastPos != QPoint(-1, -1))
    {
        QPainter painter(&m_img);

        br->release(painter, ppos);

        update();


        lastPos = QPoint(-1, -1);
    }
}

void PaintArea::mouseMoveEvent(QMouseEvent *event)
{

    if (BrushRegistry::get().current == nullptr) return;

    Brush * br = BrushRegistry::get().current->brush;

    float scale = (float)m_img.width() / (float)this->width();
    QPoint ppos = event->pos() * scale;

    if (event->buttons() & Qt::LeftButton && lastPos != QPoint(-1, -1))
    {
        QPainter painter(&m_img);
        br->move(painter, lastPos, ppos);
        update();

        lastPos = ppos;
    }
}

void PaintArea::paintEvent(QPaintEvent * /*event*/)
{
    if (m_img.isNull()) return;

    QPainter painter(this);
    QImage tmp = m_img.scaled(this->size());
    painter.drawImage(QPoint(0,0), tmp);
}
