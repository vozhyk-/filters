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

#include "FunctionFilter.hpp"

void FunctionFilter::apply(QImage &image) const
{
    for (int y = 0; y < image.height(); y++)
        for (int x = 0; x < image.width(); x++)
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
    return Filter::clamp((channel + argOffset) * slope + offset);
}
