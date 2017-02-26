#include "Filter.hpp"

#include <iostream>

using namespace std;

ostream &operator<<(ostream &stream, const QPoint &point);

void Filter::apply(QImage &image)
{
    QImage original{image};

    for (int y = 0; y < image.height(); y++) {
        for (int x = 0; x < image.width(); x++) {
            applyAtPoint(original, image, QPoint{x, y});
        }
    }
}

void Filter::applyAtPoint(
    const QImage &original, QImage &image, const QPoint &toProcess)
{
    image.setPixel(toProcess, colorAtPoint(original, toProcess));
}

QRgb Filter::colorAtPoint(const QImage &original, const QPoint &point)
{
    QPoint anchor{1, 1};
    QRect rect{point - anchor, size()};

    tuple<int, int, int> result{0, 0, 0};

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

            std::get<0>(result) += qRed(rgb) * multiplier;
            std::get<1>(result) += qGreen(rgb) * multiplier;
            std::get<2>(result) += qBlue(rgb) * multiplier;
        }
    }

    std::get<0>(result) /= divisor;
    std::get<1>(result) /= divisor;
    std::get<2>(result) /= divisor;

    return qRgb(
        std::get<0>(result),
        std::get<1>(result),
        std::get<2>(result));
}

ostream &operator<<(ostream &stream, const QPoint &point) {
    stream << "(" << point.x() << "," << point.y() << ")";
    return stream;
}
