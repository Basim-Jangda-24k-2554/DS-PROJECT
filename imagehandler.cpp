#include "ImageHandler.h"
#include <QImage>
#include <QColor>

ImageHandler::ImageHandler() {
    pixels = nullptr;
    width = 0;
    height = 0;
}

ImageHandler::~ImageHandler() {
    freePixels();
}

void ImageHandler::freePixels() {
    if (pixels) {
        delete[] pixels;
        pixels = nullptr;
    }
}

// Load image and convert to grayscale
bool ImageHandler::loadImage(const QString &filePath) {
    freePixels();

    QImage image;
    if (!image.load(filePath)) return false;

    width = image.width();
    height = image.height();

    pixels = new unsigned char[width * height];

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            QColor color = image.pixelColor(x, y);
            // Convert to grayscale
            unsigned char gray = static_cast<unsigned char>((color.red() + color.green() + color.blue()) / 3);
            pixels[y * width + x] = gray;
        }
    }

    return true;
}

// Get pixel array
unsigned char* ImageHandler::getPixels() const {
    return pixels;
}

// Get width
int ImageHandler::getWidth() const {
    return width;
}

// Get height
int ImageHandler::getHeight() const {
    return height;
}

// Build QImage from pixels array
QImage ImageHandler::buildImageFromPixels() {
    QImage image(width, height, QImage::Format_Grayscale8);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            unsigned char gray = pixels[y * width + x];
            image.setPixelColor(x, y, QColor(gray, gray, gray));
        }
    }
    return image;
}

// Save QImage to file
bool ImageHandler::saveImage(const QString &filePath, QImage &image) {
    return image.save(filePath);
}
