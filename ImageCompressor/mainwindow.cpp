#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "ImageHandler.h"
#include "Huffman.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QImage>
#include <QString>
#include <QFile>
#include <QColor>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connect buttons
    connect(ui->btnLoad, &QPushButton::clicked, this, &MainWindow::onLoadImage);
    connect(ui->btnCompress, &QPushButton::clicked, this, &MainWindow::onCompressImage);
    connect(ui->btnDecompress, &QPushButton::clicked, this, &MainWindow::onDecompressImage);

    imageHandler = new ImageHandler();
}

MainWindow::~MainWindow()
{
    delete imageHandler;
    delete ui;
}

// LOAD IMAGE 
void MainWindow::onLoadImage() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open Image", "", "Images (*.png *.jpg *.bmp)");
    if (fileName.isEmpty()) return;

    if (!imageHandler->loadImage(fileName)) {
        QMessageBox::warning(this, "Error", "Failed to load image.");
        return;
    }

    loadedImagePath = fileName; // store original image path

    QImage img = imageHandler->buildImageFromPixels();
    ui->lblOriginal->setPixmap(QPixmap::fromImage(img));
    ui->lblOriginal->setScaledContents(true);

    ui->lblRatio->setText("Compression Ratio: N/A");
}

// COMPRESS IMAGE 
void MainWindow::onCompressImage() {
    if (!imageHandler->getPixels()) {
        QMessageBox::warning(this, "Error", "Load an image first.");
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(this, "Save Compressed File", "", "Huffman Files (*.huff)");
    if (fileName.isEmpty()) return;

    Huffman huff;
    int width = imageHandler->getWidth();
    int height = imageHandler->getHeight();
    unsigned char *pixels = imageHandler->getPixels();

    if (!huff.compressToFile(pixels, width, height, fileName)) {
        QMessageBox::warning(this, "Error", "Failed to compress image.");
        return;
    }

    // Calculate compression ratio
    QFile originalFile(loadedImagePath);
    QFile compressedFile(fileName);

    if (originalFile.exists() && compressedFile.exists()) {
        double ratio = double(originalFile.size()) / double(compressedFile.size());
        ui->lblRatio->setText(QString("Compression Ratio: %1").arg(ratio, 0, 'f', 2));
    }

    QMessageBox::information(this, "Success", "Image compressed successfully.");
}

//  DECOMPRESS IMAGE 
void MainWindow::onDecompressImage() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open Compressed File", "", "Huffman Files (*.huff)");
    if (fileName.isEmpty()) return;

    Huffman huff;
    unsigned char *pixels = nullptr;
    int width, height;

    if (!huff.decompressFromFile(pixels, width, height, fileName)) {
        QMessageBox::warning(this, "Error", "Failed to decompress file.");
        return;
    }

    // Build QImage from pixels
    QImage img(width, height, QImage::Format_Grayscale8);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            unsigned char gray = pixels[y * width + x];
            img.setPixelColor(x, y, QColor(gray, gray, gray));
        }
    }

    ui->lblDecompressed->setPixmap(QPixmap::fromImage(img));
    ui->lblDecompressed->setScaledContents(true);

    QMessageBox::information(this, "Success", "Image decompressed successfully.");

    // Free memory
    delete[] pixels;
}
