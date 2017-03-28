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

#ifndef DITHER_HPP
#define DITHER_HPP

#include "Filter.hpp"

#include <memory>
#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <functional>

class Dither : public Filter
{
public:
    Dither(int numLevels) :
        numLevels{numLevels}, levels{generateLevels()}
    {
    }
 
    void apply(QImage &image) const override;

    static std::unique_ptr<Dither> parse(const QString &input) {
        QStringList fields = input.split(":");

        int numLevels = fields[0].toInt();

        return std::make_unique<Dither>(numLevels);
    }

private:
    int numLevels;

    using levelsVector = std::vector<unsigned char>;

    levelsVector levels;

    std::random_device device{};
    std::mt19937 engine{device()};
    std::uniform_real_distribution<double> distribution{};
    std::function<double()> random_threshold = std::bind(distribution, engine);

    levelsVector generateLevels();

    void applyAtPoint(
        QImage &image, const QPoint &toProcess) const;
    unsigned char levelAtPoint(
        const QImage &image, const QPoint &point) const;
    unsigned char threshold(unsigned char level) const;
    std::pair<unsigned char, unsigned char> neighbors(
        unsigned char level) const;
};

#endif // DITHER_HPP
