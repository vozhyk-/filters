#include "FunctionFilter.hpp"

void FunctionFilter::apply(QImage &image) const
{
    for (int y = 0; y < image.height(); y++)
        for (int x = 0; x < image.height(); x++)
            applyAtPoint(image, QPoint{x, y});
}

void FunctionFilter::applyAtPoint(QImage &image, const QPoint &toProcess) const
{
    image.setPixel(toProcess, colorAtPoint(image, toProcess));
}

QRgb FunctionFilter::colorAtPoint(QImage &image, const QPoint &point) const
{
    QRgb input = image.pixel(point);

    int red = colorForChannel(qRed(input));
    int green = colorForChannel(qGreen(input));
    int blue = colorForChannel(qBlue(input));

    return qRgb(red, green, blue);
    
}

unsigned char FunctionFilter::colorForChannel(unsigned char channel) const
{
    return Filter::clamp(channel * slope + offset);
}
