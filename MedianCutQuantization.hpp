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

#ifndef MEDIAN_CUT_QUANTIZATION_HPP
#define MEDIAN_CUT_QUANTIZATION_HPP

#include "Filter.hpp"
#include "ColorTree.hpp"

#include <memory>
#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <functional>

class MedianCutQuantization : public Filter
{
public:
    MedianCutQuantization(int numColors) :
        numColors{numColors}
    {
    }
 
    void apply(QImage &image) const override;

    static std::unique_ptr<MedianCutQuantization> parse(const QString &input) {
        QStringList fields = input.split(":");

        int numColors = fields[0].toInt();

        return std::make_unique<MedianCutQuantization>(numColors);
    }

private:
    int numColors;

    ColorTree generateColors(const QImage &image) const;

    void applyAtPoint(
        QImage &image, ColorTree &colors, const QPoint &toProcess) const;
    QRgb colorAtPoint(
        const QImage &image, ColorTree &colors, const QPoint &point) const;
    QRgb threshold(ColorTree &colors, QRgb color) const;
};

#endif // MEDIAN_CUT_QUANTIZATION_HPP
