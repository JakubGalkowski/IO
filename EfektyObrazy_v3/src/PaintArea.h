#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QWidget>

class PaintArea : public QWidget
{
    friend class MainWindow;

    Q_OBJECT
public:
    explicit PaintArea(QWidget *parent = nullptr);
    void setImage(QImage & img)
    {
        m_img = img;
        update();
    }

protected:
    QImage m_img;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

signals:

};

#endif // PAINTAREA_H
