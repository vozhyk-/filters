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

#include <cassert>

using namespace std;

template <typename T> std::ostream &operator<<(
    std::ostream& out, const std::vector<T>& v);
QRgb greyRgb(QRgb color);


MedianCutQuantization::colorsVector MedianCutQuantization::generateColors()
{
    int maxColor = 255;
    double d = maxColor / (numColors - 1);

    cout << "Number of colors: " << numColors
         << ", step: " << d << endl;
    
    MedianCutQuantization::colorsVector result{};
    result.reserve(numColors);
    for (int i = 0; i < numColors; i++)
        result.push_back(d * i); // TODO Fix numColors == 3

    cout << "Colors: " << result << endl;
    return result;
}

template <typename T> std::ostream &operator<<(
    std::ostream& out, const std::vector<T>& v) {

    if (!v.empty()) {
        out << '[';
        for (auto i: v)
            out << int(i) << ", ";
        out << "\b\b]";
    }
    return out;
}

void MedianCutQuantization::apply(QImage &image) const
{
    Filter::makeMonochrome(image);

    for (int y = 0; y < image.height(); y++)
        for (int x = 0; x < image.width(); x++)
            applyAtPoint(image, QPoint{x, y});
}


void MedianCutQuantization::applyAtPoint(
    QImage &image, const QPoint &toProcess) const
{
    image.setPixel(toProcess, colorAtPoint(image, toProcess));
}

QRgb MedianCutQuantization::colorAtPoint(
    const QImage &image, const QPoint &point) const
{
    return threshold(image.pixel(point));
}

QRgb MedianCutQuantization::threshold(QRgb color) const
{
    QRgb lower, higher;
    tie(lower, higher) = neighbors(color);

    double threshold = random_threshold();
    return double(color - lower) / (higher - lower) > threshold ?
        higher : lower;
}

pair<QRgb, QRgb> MedianCutQuantization::neighbors(QRgb color) const
{
    auto higher = upper_bound(colors.begin(), colors.end(), color);
    if (higher == colors.end())
        --higher;

    auto lower = higher - 1;
    assert(lower >= colors.begin());

    return make_pair(*lower, *higher);
}
