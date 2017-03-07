#include "MedianFilter.hpp"

#include <algorithm>

using namespace std;


void makeMonochrome(QImage &image);
QRgb monochromePixel(QRgb pixel);

void MedianFilter::apply(QImage &image) const
{
    makeMonochrome(image);
    QImage original{image};

    for (int y = 0; y < image.height(); y++)
        for (int x = 0; x < image.width(); x++)
            applyAtPoint(original, image, QPoint{x, y});
}

void makeMonochrome(QImage &image)
{
    for (int y = 0; y < image.height(); y++)
        for (int x = 0; x < image.width(); x++)
            image.setPixel(x, y, monochromePixel(image.pixel(x, y)));
}

QRgb monochromePixel(QRgb pixel)
{
    /*
    int channel =
        0.3 * qRed(pixel) +
        0.58 * qGreen(pixel) +
        0.12 * qBlue(pixel);
    */
    int channel = qGray(pixel);
    return qRgb(channel, channel, channel);
}

void MedianFilter::applyAtPoint(
    const QImage &original, QImage &image, const QPoint &toProcess) const
{
    image.setPixel(toProcess, colorAtPoint(original, toProcess));
}

QRgb MedianFilter::colorAtPoint(
    const QImage &original, const QPoint &point) const
{
    QRect rect{point - anchor, size()};

    vector<int> channels{};

    for (int y = rect.y(), filterY = 0;
         y < rect.y() + rect.height();
         y++, filterY++) {
        for (int x = rect.x(), filterX = 0;
             x < rect.x() + rect.width();
             x++, filterX++) {

            QPoint realPos{
                Filter::clamp(x, 0, original.width()),
                Filter::clamp(y, 0, original.height())};

            QRgb rgb = original.pixel(realPos);
            channels.push_back(qRed(rgb));
        }
    }

    sort(channels.begin(), channels.end());

    int numPixels = size().width() * size().height();
    int channel = channels[numPixels / 2];

    return qRgb(channel, channel, channel);
}
