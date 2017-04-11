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

using namespace std;


void ColorTree::splitInto(int numColors)
{
}

using ColorTuple = tuple<long long, long long, long long>;

ColorTuple operator+(ColorTuple first, ColorTuple second);
void operator+=(ColorTuple first, ColorTuple second);

QRgb ColorTree::Bucket::average(vector<QRgb> pixels)
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

void operator+=(ColorTuple first, ColorTuple second)
{
    first = first + second;
}

ColorTuple operator+(ColorTuple first, ColorTuple second)
{
    return ColorTuple{
        get<0>(first) + get<0>(second),
        get<1>(first) + get<1>(second),
        get<2>(first) + get<2>(second)};
}
