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

#ifndef FUNCTION_FILTER_H
#define FUNCTION_FILTER_H

#include "Filter.hpp"

class FunctionFilter : public Filter
{
public:
    FunctionFilter(double slope, int argOffset, int offset) :
        slope{slope}, argOffset{argOffset}, offset{offset}
    {
    }

    void apply(QImage &image) const override;

private:
    double slope;
    int argOffset;
    int offset;

    void applyAtPoint(QImage &image, const QPoint &toProcess) const;
    QRgb colorAtPoint(QImage &image, const QPoint &point) const;
    unsigned char colorForChannel(unsigned char channel) const;
};

#endif // FUNCTION_FILTER_H
