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

#ifndef CONVOLUTION_FILTER_HPP
#define CONVOLUTION_FILTER_HPP

#include "Filter.hpp"

#include <QVector>

class ConvolutionFilter : public Filter
{
public:
    using matrixT = QVector<int>;

    ConvolutionFilter(int columns, matrixT matrix,
                      QPoint anchor, int divisor, int offset) :
        columns{columns}, matrix{matrix}, anchor{anchor},
        divisor{divisor}, offset{offset}
    {
    }

    void apply(QImage &image) const override;

private:
    int columns;
    matrixT matrix;
    QPoint anchor;
    int divisor;
    int offset;

    QSize size() const {
        return QSize{columns, matrix.length() / columns};
    }

    int get(int x, int y) const { return matrix[y * columns + x]; }

    void applyAtPoint(
        const QImage &original, QImage &image, const QPoint &toProcess) const;
    QRgb colorAtPoint(const QImage &original, const QPoint &point) const;
};

#endif // CONVOLUTION_FILTER_HPP
