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

#ifndef FILTER_H
#define FILTER_H

#include <QImage>

class Filter
{
public:
    virtual void apply(QImage &image) const = 0;

    static int clamp(int channel)
    {
        return clamp(channel, 0, 256);
    }

    //! clamp inside the [start, end) range:
    //! if value == end, return end - 1
    static int clamp(int value, int start, int end)
    {
        if (value >= end)
            return end - 1;
        else if (value < start)
            return start;
        else
            return value;
    }


    static QRgb monochromePixel(QRgb pixel)
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
    
    static void makeMonochrome(QImage &image)
    {
        for (int y = 0; y < image.height(); y++)
            for (int x = 0; x < image.width(); x++)
                image.setPixel(x, y, monochromePixel(image.pixel(x, y)));
    }
};

#endif // FILTER_H
