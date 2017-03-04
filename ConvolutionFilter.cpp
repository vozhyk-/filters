#include "ConvolutionFilter.hpp"

#include <iostream>

using namespace std;

int clamp(int value);
ostream &operator<<(ostream &stream, const QPoint &point);

void ConvolutionFilter::apply(QImage &image) const
{
    QImage original{image};

    for (int y = 0; y < image.height(); y++) {
        for (int x = 0; x < image.width(); x++) {
            applyAtPoint(original, image, QPoint{x, y});
        }
    }
}

void ConvolutionFilter::applyAtPoint(
    const QImage &original, QImage &image, const QPoint &toProcess) const
{
    image.setPixel(toProcess, colorAtPoint(original, toProcess));
}

QRgb ConvolutionFilter::colorAtPoint(
    const QImage &original, const QPoint &point) const
{
    QRect rect{point - anchor, size()};

    int resultR{0};
    int resultG{0};
    int resultB{0};

    for (int y = rect.y(), filterY = 0;
         y < rect.y() + rect.height();
         y++, filterY++) {
        for (int x = rect.x(), filterX = 0;
             x < rect.x() + rect.width();
             x++, filterX++) {

            if (x < 0 || x >= original.width() ||
                y < 0 || y >= original.height()) {
                continue;
            }

            QRgb rgb = original.pixel(x, y);
            int multiplier = get(filterX, filterY);

            resultR += qRed(rgb) * multiplier;
            resultG += qGreen(rgb) * multiplier;
            resultB += qBlue(rgb) * multiplier;
        }
    }

    resultR = clamp(resultR / divisor + offset);
    resultG = clamp(resultG / divisor + offset);
    resultB = clamp(resultB / divisor + offset);

    return qRgb(resultR, resultG, resultB);
}

int clamp(int value)
{
    if (value > 255)
        return 255;
    else if (value < 0)
        return 0;
    else
        return value;
}

ostream &operator<<(ostream &stream, const QPoint &point) {
    stream << "(" << point.x() << "," << point.y() << ")";
    return stream;
}
