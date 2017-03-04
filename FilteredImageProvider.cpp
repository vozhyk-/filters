#include "FilteredImageProvider.hpp"

#include <iostream>
#include <memory>

#include "ConvolutionFilter.hpp"
#include "FunctionFilter.hpp"

using namespace std;

using FilterVector = vector<unique_ptr<Filter>>;

QString imagePathPortion(const QString &id);
QString filterPortion(const QString &id);
FilterVector parseFilters(const QString &input);
unique_ptr<Filter> parseFilter(const QString &input);
unique_ptr<ConvolutionFilter> parseConvolutionFilter(const QString &input);
unique_ptr<FunctionFilter> parseFunctionFilter(const QString &input);

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

    int slope = fields[0].toInt();
    int offset = fields[1].toInt();

    return make_unique<FunctionFilter>(slope, offset);
}

ostream &operator<<(ostream &stream, const QString &string) {
    stream << string.toUtf8().data();
    return stream;
}
