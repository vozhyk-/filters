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

#include "FilteredImageProvider.hpp"

#include <iostream>
#include <memory>

#include "ConvolutionFilter.hpp"
#include "FunctionFilter.hpp"
#include "MedianFilter.hpp"

using namespace std;

using FilterVector = vector<unique_ptr<Filter>>;

QString imagePathPortion(const QString &id);
QString filterPortion(const QString &id);
FilterVector parseFilters(const QString &input);
unique_ptr<Filter> parseFilter(const QString &input);
unique_ptr<ConvolutionFilter> parseConvolutionFilter(const QString &input);
unique_ptr<FunctionFilter> parseFunctionFilter(const QString &input);
unique_ptr<MedianFilter> parseMedianFilter(const QString &input);

ostream &operator<<(ostream &stream, const QString &string);

QImage FilteredImageProvider::requestImage(
    const QString &id, QSize *size, const QSize &requestedSize)
{
    Q_UNUSED(size);
    Q_UNUSED(requestedSize);

    QImage image{imagePathPortion(id)};
    FilterVector filters = parseFilters(filterPortion(id));

    for (auto &filter: filters)
        filter->apply(image);

    return image;
}

QString imagePathPortion(const QString &id)
{
    QString url = id.section(';', 1, 1);
    return QUrl::fromUserInput(url).toLocalFile();
}

QString filterPortion(const QString &id)
{
    return id.section(';', 0, 0);
}

FilterVector parseFilters(const QString &input)
{
    QStringList inputs = input.split("/");
    FilterVector result{};
    transform(inputs.begin(), inputs.end(),
              back_inserter(result), parseFilter);
    return result;
}

unique_ptr<Filter> parseFilter(const QString &input)
{
    QString type = input.section(':', 0, 0);
    QString rest = input.section(':', 1);

    if (type == "convolution")
        return parseConvolutionFilter(rest);
    else if (type == "function")
        return parseFunctionFilter(rest);
    else if (type == "median")
        return parseMedianFilter(rest);
    else
        throw logic_error{"Not implemented"};
}

unique_ptr<ConvolutionFilter> parseConvolutionFilter(const QString &input)
{
    QStringList fields = input.split(":");
    int columns = fields[0].toInt();

    ConvolutionFilter::matrixT matrix{};
    for (QString el : fields[1].split(","))
        matrix.append(el.toInt());

    QStringList anchorFields = fields[2].split(",");
    QPoint anchor{anchorFields[0].toInt(), anchorFields[1].toInt()};

    int divisor = fields[3].toInt();
    int offset = fields[4].toInt();

    return make_unique<ConvolutionFilter>(
        columns, matrix, anchor, divisor, offset);
}

unique_ptr<FunctionFilter> parseFunctionFilter(const QString &input)
{
    QStringList fields = input.split(":");

    double slope = fields[0].toDouble();
    int argOffset = fields[1].toInt();
    int offset = fields[2].toInt();

    return make_unique<FunctionFilter>(slope, argOffset, offset);
}

unique_ptr<MedianFilter> parseMedianFilter(const QString &input)
{
    Q_UNUSED(input);
    return make_unique<MedianFilter>();
}

ostream &operator<<(ostream &stream, const QString &string) {
    stream << string.toUtf8().data();
    return stream;
}
