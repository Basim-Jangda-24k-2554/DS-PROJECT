#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ImageHandler.h"
#include "Huffman.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onLoadImage();
    void onCompressImage();
    void onDecompressImage();

private:
    Ui::MainWindow *ui;
    ImageHandler *imageHandler;
     QString loadedImagePath;
};

#endif // MAINWINDOW_H
