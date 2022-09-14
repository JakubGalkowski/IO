#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    friend class History;
    friend class PaintArea;
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void resizeEvent(QResizeEvent *event) override;

protected:
    void loadImgFromPath(QString path);
    void updateImages();
    void updateHistoryView();

protected:
    QImage imgOriginal;

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
