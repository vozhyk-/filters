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

#include "Dither.hpp"

#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <functional>

using namespace std;

template <typename T> std::ostream &operator<<(
    std::ostream& out, const std::vector<T>& v);
QRgb greyRgb(unsigned char level);


Dither::levelsVector Dither::generateLevels()
{
    int maxLevel = 255;
    double d = maxLevel / (numLevels - 1);

    cout << "Number of levels: " << numLevels
         << ", step: " << d << endl;
    
    Dither::levelsVector result{};
    result.reserve(numLevels);
    for (int i = 0; i < numLevels; i++)
        result.push_back(d * i); // TODO Fix numLevels == 3

    cout << "Levels: " << result << endl;
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

/*
Dither::levelsVector Dither::generateLevels()
{
    random_device device{};
    mt19937 mersenne_engine(device());
    uniform_int_distribution<int> dist(0, 255);

    auto gen = std::bind(dist, mersenne_engine);
    Dither::levelsVector result(numLevels);
    generate(begin(result), end(result), gen);

    return result;
}
*/

void Dither::apply(QImage &image) const
{
    Filter::makeMonochrome(image);

    for (int y = 0; y < image.height(); y++)
        for (int x = 0; x < image.width(); x++)
            applyAtPoint(image, QPoint{x, y});
}


void Dither::applyAtPoint(
    QImage &image, const QPoint &toProcess) const
{
    image.setPixel(toProcess, greyRgb(levelAtPoint(image, toProcess)));
}

QRgb greyRgb(unsigned char level)
{
    return qRgb(level, level, level);
}

unsigned char Dither::levelAtPoint(
    const QImage &image, const QPoint &point) const
{
    return image.pixel(point);
}
