#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QFileDialog>
#include <QStringListModel>
#include <QDebug>
#include <QDesktopServices>
#include <QPainter>
#include <QMouseEvent>

#include "filters/FilterRegistry.h"
#include "History.h"
#include "Action.h"
#include "brushes/BrushRegistry.h"

cv::Mat fromImage(QImage &img, int format)
{
    return cv::Mat(img.height(), img.width(), format, img.bits(), img.bytesPerLine());
}

QImage toImage(cv::Mat &mat, QImage::Format format)
{
    return QImage(mat.data, mat.cols, mat.rows, mat.step, format);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->btnLoad, & QPushButton::pressed, this, [=]()
    {
        QFileDialog dialog(this);
        dialog.setFileMode(QFileDialog::ExistingFile);
        dialog.setNameFilter("Images (*.png *.jpg *.jpeg *.bmp *.tiff)");
        dialog.setViewMode(QFileDialog::Detail);

        if(dialog.exec())
        {
            QStringList fileNames = dialog.selectedFiles();
            if (fileNames.size() == 1) loadImgFromPath(fileNames[0]);
        }

    });

    connect(ui->btnSave, & QPushButton::pressed, this, [=]()
    {
        if (ui->imgEdited->m_img.isNull()) return;

        QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image File"), QString(), tr("Images (*.png)"));

        if(!fileName.endsWith(".png")) fileName += ".png";
        if (!fileName.isEmpty()) ui->imgEdited->m_img.save(fileName);
    });


    ui->listHistory->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->listBrushes->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->listExtensions->setEditTriggers(QAbstractItemView::NoEditTriggers);


    {
        QStringList * list = new QStringList;
        for (FilterRegistry::Entry & e : FilterRegistry::get().entries) {
            list->append(QString::fromStdString(e.name));
        }
        QStringListModel * model = new QStringListModel(*list);
        ui->listExtensions->setModel(model);
    }

    {
        QStringList * list = new QStringList;
        for (BrushRegistry::Entry & e : BrushRegistry::get().entries) {
            list->append(QString::fromStdString(e.name));
        }
        QStringListModel * model = new QStringListModel(*list);
        ui->listBrushes->setModel(model);
    }

    connect(ui->listBrushes, & QAbstractItemView::clicked, this, [=](const QModelIndex & index)
    {
        ui->listExtensions->clearSelection();
        int i = index.row();

        BrushRegistry::get().setCurrent(i);
    });

    connect(ui->listExtensions, & QAbstractItemView::doubleClicked, this, [=](const QModelIndex & index)
    {
        ui->listExtensions->clearSelection();
        int i = index.row();

        FilterRegistry::Entry & fe = FilterRegistry::get().entries[i];
        History::get().add(fe.filter, ui->imgEdited->m_img);
        cv::Mat mat = fromImage(ui->imgEdited->m_img, CV_8UC4);
        FilterRegistry::get().entries[i].filter->use(mat);

        ui->imgEdited->update();

        updateHistoryView();
        updateImages();
    });

    connect(ui->btnUndo, & QPushButton::pressed, this, [=]()
    {
        auto ent = History::get().undo(ui->imgEdited->m_img);
        if (!ent.isNull()) ui->imgEdited->setImage(ent.prevImg);
        updateHistoryView();
        updateImages();
    });

    connect(ui->btnRedo, & QPushButton::pressed, this, [=]()
    {
        auto ent = History::get().redo(ui->imgEdited->m_img);
        if (!ent.isNull()) ui->imgEdited->setImage(ent.prevImg);
        updateHistoryView();
        updateImages();
    });

    connect(ui->btnExts, & QPushButton::pressed, this, [=]()
    {
        QDesktopServices::openUrl(QUrl("rozszerzenia"));
    });
}


void MainWindow::updateHistoryView()
{
    QStringList * list = new QStringList;

    for (auto & ent : History::get().undoHistory) {
        list->append(QString::fromStdString(ent.act.m_name));
    }

    QStringListModel * model = new QStringListModel(*list);
    ui->listHistory->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    updateImages();
}

void MainWindow::loadImgFromPath(QString path)
{
     QString fileName = path.mid(1+path.lastIndexOf(QDir::separator()));
     setWindowTitle("Edytowanie @ " + fileName);

     imgOriginal.load(path, "rgb32");
     ui->imgEdited->setImage(imgOriginal);

     updateImages();
}

void MainWindow::updateImages()
{
    if (imgOriginal.format() == QImage::Format_Invalid) return;

    QSize si = ui->widgetImages->size();
    QSize iSi = imgOriginal.size();
    double ratio = (double)iSi.width()/iSi.height();
    int spaceBetween = 10;

    ui->imgOriginal->setPixmap(QPixmap::fromImage(imgOriginal));
//    ui->imgEdited->setPixmap(QPixmap::fromImage(imgEdited));

    int hWidth = (si.width() - spaceBetween) / 2;

    if (hWidth * 1/ratio < si.height())
    {
        int hight = hWidth * 1/ratio;
        int centerHight = si.height()/2 - hight/2;

        ui->imgOriginal->move(0,centerHight);
        ui->imgOriginal->resize(hWidth, hight);

        ui->imgEdited->move(hWidth + spaceBetween, centerHight);
        ui->imgEdited->resize(hWidth, hight);


    }
    else
    {
        int wid = ratio * si.height();
        int centerHight = si.height()/2 - si.height()/2;

        ui->imgOriginal->move(0,centerHight);
        ui->imgOriginal->resize(wid, si.height());

        ui->imgEdited->move(wid + spaceBetween, si.height());
        ui->imgEdited->resize(wid, centerHight);

    }

//    ui->imgEdited->update();
}
