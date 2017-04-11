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

#ifndef COLOR_TREE_HPP
#define COLOR_TREE_HPP

#include <vector>
#include <memory>

#include <QImage>

class ColorTree
{
public:
    enum class Channel {
        Red, Green, Blue
    };

    ColorTree(std::vector<QRgb> allPixels)
        : root{std::make_shared<Bucket>(allPixels)}, numBuckets{1}
    {
    }

    class Bucket
    {
    public:
        using ColorTuple = std::tuple<
            unsigned long long,
            unsigned long long,
            unsigned long long>;
        using ColorRange = std::pair<QRgb, QRgb>;

        Bucket(std::vector<QRgb> pixels)
            : pixels{pixels}, resultingColor{average(pixels)},
              range{getRange(pixels)}
        {
        }

        void splitAtMedian(Channel ch);

        std::shared_ptr<Bucket> left{nullptr};
        std::shared_ptr<Bucket> right{nullptr};

        std::vector<QRgb> pixels;
        QRgb resultingColor;
        ColorRange range;

    private:    
        static QRgb average(std::vector<QRgb> pixels);
        static ColorRange getRange(std::vector<QRgb> pixels);
    };

    void splitInto(int numColors);

    std::shared_ptr<Bucket> root;

private:
    int numBuckets;
    std::pair<Channel, std::shared_ptr<Bucket>> findWidestBucket() const;
};

#endif // COLOR_TREE_HPP
