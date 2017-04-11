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

#include "ColorTree.hpp"

#include <iostream>

using namespace std;

using Channel = ColorTree::Channel;
using Bucket = ColorTree::Bucket;
using ColorTuple = ColorTree::Bucket::ColorTuple;
using ColorRange = ColorTree::Bucket::ColorRange;


static const std::vector<Channel> allChannels{
    Channel::Red,
    Channel::Green,
    Channel::Blue};


void ColorTree::splitInto(int numColors)
{
    // 1. Find a bucket with the highest range of a channel
    // 2. Sort it and split into 2
    // 3. Repeat until numBuckets == numColors
}

pair<Channel, shared_ptr<Bucket>> ColorTree::findWidestBucket() const
{
    return make_pair(Channel::Red, root);
}


ColorTuple operator+(ColorTuple first, ColorTuple second);
ColorTuple &operator+=(ColorTuple &first, const ColorTuple &second);

QRgb Bucket::average(vector<QRgb> pixels)
{
    ColorTuple sum;
    auto n = pixels.size();

    for (auto i: pixels)
        sum += ColorTuple(qRed(i), qBlue(i), qGreen(i));

    return qRgb(
        get<0>(sum) / n,
        get<1>(sum) / n,
        get<2>(sum) / n);
}

ColorTuple &operator+=(ColorTuple &first, const ColorTuple &second)
{
    first = first + second;
    return first;
}

ColorTuple operator+(ColorTuple first, ColorTuple second)
{
    return ColorTuple{
        get<0>(first) + get<0>(second),
        get<1>(first) + get<1>(second),
        get<2>(first) + get<2>(second)};
}

unsigned char getChannel(Channel ch, QRgb color);
void setChannel(Channel ch, QRgb &dest, QRgb source);

ColorRange Bucket::getRange(std::vector<QRgb> pixels)
{
    QRgb min = qRgb(255, 255, 255);
    QRgb max = qRgb(0, 0, 0);
    
    for (auto i: pixels) {
        for (auto ch: allChannels) {
            if (getChannel(ch, i) < getChannel(ch, min))
                setChannel(ch, min, i);
            if (getChannel(ch, i) > getChannel(ch, max))
                setChannel(ch, max, i);
        }
    }

    return ColorRange{min, max};
}

unsigned char getChannel(Channel ch, QRgb color)
{
    switch (ch) {
    case Channel::Red:
        return qRed(color);
    case Channel::Green:
        return qGreen(color);
    case Channel::Blue:
        return qBlue(color);
    default:
        throw new invalid_argument("Invalid channel");
    }
}

void setChannel(Channel ch, QRgb &dest, QRgb source)
{
    switch (ch) {
    case Channel::Red:
        dest = qRgb(qRed(source), qGreen(dest), qBlue(dest));
        break;
    case Channel::Green:
        dest = qRgb(qRed(dest), qGreen(source), qBlue(dest));
        break;
    case Channel::Blue:
        dest = qRgb(qRed(dest), qGreen(dest), qBlue(source));
        break;
    default:
        throw new invalid_argument("Invalid channel");
    }
}
