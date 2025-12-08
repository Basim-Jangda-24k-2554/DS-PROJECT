#ifndef IMAGEHANDLER_H
#define IMAGEHANDLER_H

#include <QString>
#include <QImage>

class ImageHandler {
public:
    ImageHandler();
    ~ImageHandler();

    // Load image from file and store pixels in 1D array
    bool loadImage(const QString &filePath);

    // Save QImage to file
    bool saveImage(const QString &filePath, QImage &image);

    // Get pixels as 1D array
    unsigned char* getPixels() const;

    // Get image width and height
    int getWidth() const;
    int getHeight() const;

    // Build QImage from pixels array
    QImage buildImageFromPixels();

private:
    unsigned char* pixels; // stores grayscale pixel values
    int width;
    int height;

    void freePixels();
};

#endif // IMAGEHANDLER_H
