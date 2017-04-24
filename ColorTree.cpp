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
#include <cassert>

using namespace std;
using namespace std::experimental;

using Channel = ColorTree::Channel;
using Bucket = ColorTree::Bucket;
using ColorTuple = ColorTree::Bucket::ColorTuple;
using ColorRange = ColorTree::Bucket::ColorRange;


static const std::vector<Channel> allChannels{
    Channel::Red,
    Channel::Green,
    Channel::Blue};


unsigned char getChannel(Channel ch, QRgb color);
void setChannel(Channel ch, QRgb &dest, QRgb source);


void ColorTree::splitInto(int numColors)
{
    while (numBuckets < numColors) {
        // 1. Find a bucket with the highest range of a channel
        Channel ch;
        shared_ptr<Bucket> bucket;
        tie(ch, bucket) = findWidestBucket();

        // 2. Sort it by the channel with the highest range
        sort(bucket->pixels.begin(), bucket->pixels.end(),
             [=](QRgb first, QRgb second) {
                 return getChannel(ch, first) < getChannel(ch, second);
             });

        // 3. Split it into 2
        //cout << "Splitting into 2 parts" << endl;
        // cout << "Splitting by channel " << int(ch) << endl;
        auto begin = bucket->pixels.begin();
        auto end = bucket->pixels.end();
        // cout << "Original length: " << end - begin << endl;
        if (end - begin <= 1)
            goto end;

        auto half = begin + bucket->pixels.size() / 2;
        bucket->left = make_shared<Bucket>(vector<QRgb>(begin, half));
        bucket->right = make_shared<Bucket>(vector<QRgb>(half, end));
        // cout << "Split into "
        //      << bucket->left->pixels.size() << " and "
        //      << bucket->right->pixels.size() << " pixels." << endl;
        bucket->pixels = vector<QRgb>{};
        numBuckets++;
        cout << numBuckets << " buckets." << endl;
    }

end:
    cout << "Done splitting." << endl << endl;
}

pair<Channel, shared_ptr<Bucket>> ColorTree::findWidestBucket()
{
    unsigned char maxWidth = 0;
    shared_ptr<Bucket> widestBucket{nullptr};
    Channel widestChannel;
    walkInOrder<bool>(root, [&](shared_ptr<Bucket> bucket) {
        for (auto ch: allChannels) {
            unsigned char channelWidth =
                getChannel(ch, bucket->range.second) -
                getChannel(ch, bucket->range.first);
            // cout << "findWidestBucket: Channel width: "
            //      << int(channelWidth) << endl;

            if (channelWidth >= maxWidth) {
                // cout << "findWidestBucket: Current widest bucket/channel: "
                //      << int(channelWidth) << endl;
                maxWidth = channelWidth;
                widestChannel = ch;
                widestBucket = bucket;
            }
        }

        return optional<bool>();
    });

    // cout << "findWidestBucket: Widest bucket/channel: "
    //      << int(maxWidth) << endl;
    assert(widestBucket != nullptr);
    assert(widestBucket->pixels.size() != 0);
    return make_pair(widestChannel, widestBucket);
}

void ColorTree::printColor(ostream &stream, QRgb color)
{
    stream << "(";
    for (auto ch: allChannels) {
        stream << int(getChannel(ch, color)) << ", ";
    }
    stream << ")";
}

bool Bucket::contains(QRgb color)
{
    //cout << "contains?: Color: "; printColor(cout, color);
    //cout <<" Range: [";
    //printColor(cout, range.first); cout << ", ";
    //printColor(cout, range.second); cout << "]" << endl;

    for (auto ch: allChannels) {
        if (getChannel(ch, color) < getChannel(ch, range.first) ||
            getChannel(ch, color) > getChannel(ch, range.second)) {
            //cout << "No." << endl;
            return false;
        }
    }

    //cout << "Yes." << endl;
    return true;
}


ColorTuple operator+(ColorTuple first, ColorTuple second);
ColorTuple &operator+=(ColorTuple &first, const ColorTuple &second);

QRgb Bucket::average(vector<QRgb> pixels)
{
    ColorTuple sum{0, 0, 0};
    auto n = pixels.size();
    assert(n != 0);

    for (auto i: pixels)
        sum += ColorTuple(qRed(i), qGreen(i), qBlue(i));

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

ColorRange Bucket::getRange(std::vector<QRgb> pixels)
{
    if (pixels.size() == 0)
        return ColorRange{qRgb(0, 0, 0), qRgb(0, 0, 0)};

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

QRgb ColorTree::colorForPixel(QRgb pixel)
{
    auto cached = colorsForPixelsCache.find(pixel);
    if (cached != colorsForPixelsCache.end())
        return cached->second;

    optional<QRgb> result = walkInOrder<QRgb>(
        root,
        [=](shared_ptr<Bucket> bucket) {
            //cout << "Checking bucket" << endl;
            if (bucket->contains(pixel)) {
                return make_optional(bucket->resultingColor);
            } else {
                return optional<QRgb>();
            }
        });

    colorsForPixelsCache[pixel] = *result;
    return *result;
}
