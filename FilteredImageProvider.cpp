#include "FilteredImageProvider.hpp"

#include <iostream>

#include "ConvolutionFilter.hpp"

using namespace std;

QString imagePathPortion(const QString &id);
QString filterPortion(const QString &id);
vector<ConvolutionFilter> parseFilters(const QString &input);
ConvolutionFilter parseConvolutionFilter(const QString &input);

ostream &operator<<(ostream &stream, const QString &string);

QImage FilteredImageProvider::requestImage(
    const QString &id, QSize *size, const QSize &requestedSize)
{
    Q_UNUSED(size);
    Q_UNUSED(requestedSize);

    QImage image{imagePathPortion(id)};
    vector<ConvolutionFilter> filters = parseFilters(filterPortion(id));

    for (auto filter: filters)
        filter.apply(image);

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

vector<ConvolutionFilter> parseFilters(const QString &input)
{
    QStringList inputs = input.split("/");
    vector<ConvolutionFilter> result{};
    transform(inputs.begin(), inputs.end(),
              back_inserter(result), parseConvolutionFilter);
    return result;
}

ConvolutionFilter parseConvolutionFilter(const QString &input)
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

    return ConvolutionFilter{columns, matrix, anchor, divisor, offset};
}

ostream &operator<<(ostream &stream, const QString &string) {
    stream << string.toUtf8().data();
    return stream;
}
