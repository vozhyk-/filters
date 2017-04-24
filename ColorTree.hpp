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

#include <iostream>
#include <vector>
#include <memory>
#include <experimental/optional>

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

        bool contains(QRgb color);

        std::shared_ptr<Bucket> left{nullptr};
        std::shared_ptr<Bucket> right{nullptr};

        std::vector<QRgb> pixels;
        QRgb resultingColor;
        ColorRange range{0, 0};

    private:    
        static QRgb average(std::vector<QRgb> pixels);
        static ColorRange getRange(std::vector<QRgb> pixels);
    };

    template<typename T>
    using optional = std::experimental::optional<T>;

    template<typename T>
    optional<T> walkInOrder(
        std::shared_ptr<Bucket> bucket,
        std::function<optional<T> (std::shared_ptr<Bucket> bucket)> fun)
    {
        if (bucket->left && bucket->right) {
            //std::cout << "Descending left" << std::endl;
            auto result = walkInOrder(bucket->left, fun);
            if (result)
                return result;

            //std::cout << "Descending right" << std::endl;
            result = walkInOrder(bucket->right, fun);
            if (result)
                return result;
        } else {
            //std::cout << "Not descending" << std::endl;
            auto result = fun(bucket);
            if (result)
                return result;
        }

        //std::cout << "Nothing found." << std::endl;
        return optional<T>();
    }

    void splitInto(int numColors);

    std::shared_ptr<Bucket> root;

private:
    int numBuckets;
    std::pair<Channel, std::shared_ptr<Bucket>> findWidestBucket();
};

#endif // COLOR_TREE_HPP
