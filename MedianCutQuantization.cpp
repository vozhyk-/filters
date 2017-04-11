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

#include "MedianCutQuantization.hpp"
#include "ColorTree.hpp"

#include <cassert>

using namespace std;


vector<QRgb> pixels(const QImage &image);

ColorTree MedianCutQuantization::generateColors(const QImage &image) const
{
    ColorTree result{pixels(image)};
    result.splitInto(numColors);
    return result;
}

vector<QRgb> pixels(const QImage &image)
{
    vector<QRgb> result{};

    for (int y = 0; y < image.height(); y++)
        for (int x = 0; x < image.width(); x++)
            result.push_back(image.pixel(x, y));

    return result;
}

void MedianCutQuantization::apply(QImage &image) const
{
    ColorTree colors = generateColors(image);

    for (int y = 0; y < image.height(); y++)
        for (int x = 0; x < image.width(); x++)
            applyAtPoint(image, colors, QPoint{x, y});
}

void MedianCutQuantization::applyAtPoint(
    QImage &image, const ColorTree &colors, const QPoint &toProcess) const
{
    image.setPixel(toProcess, colorAtPoint(image, colors, toProcess));
}

QRgb MedianCutQuantization::colorAtPoint(
    const QImage &image, const ColorTree &colors, const QPoint &point) const
{
    return threshold(colors, image.pixel(point));
}

QRgb MedianCutQuantization::threshold(const ColorTree &colors, QRgb color) const
{
    return colors.root->resultingColor;
}
