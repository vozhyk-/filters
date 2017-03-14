/*
 * Copyright (c) 2017 Witaut Bajaryn
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "ConvolutionFilter.hpp"

#include <iostream>

using namespace std;

int clamp(int value);
ostream &operator<<(ostream &stream, const QPoint &point);

void ConvolutionFilter::apply(QImage &image) const
{
    QImage original{image};

    for (int y = 0; y < image.height(); y++)
        for (int x = 0; x < image.width(); x++)
            applyAtPoint(original, image, QPoint{x, y});
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

            QPoint realPos{
                Filter::clamp(x, 0, original.width()),
                Filter::clamp(y, 0, original.height())};

            QRgb rgb = original.pixel(realPos);
            int multiplier = get(filterX, filterY);

            resultR += qRed(rgb) * multiplier;
            resultG += qGreen(rgb) * multiplier;
            resultB += qBlue(rgb) * multiplier;
        }
    }

    resultR = Filter::clamp(resultR / divisor + offset);
    resultG = Filter::clamp(resultG / divisor + offset);
    resultB = Filter::clamp(resultB / divisor + offset);

    return qRgb(resultR, resultG, resultB);
}

ostream &operator<<(ostream &stream, const QPoint &point) {
    stream << "(" << point.x() << "," << point.y() << ")";
    return stream;
}
