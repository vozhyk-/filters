#include "FilteredImageProvider.hpp"

#include <iostream>

#include "Filter.hpp"

using namespace std;

QString imagePathPortion(const QString &id);
QString filterPortion(const QString &id);
Filter parseFilter(const QString &input);

ostream &operator<<(ostream &stream, const QString &string);

QImage FilteredImageProvider::requestImage(
    const QString &id, QSize *size, const QSize &requestedSize)
{
    Q_UNUSED(size);
    Q_UNUSED(requestedSize);

    QImage image{imagePathPortion(id)};
    Filter filter = parseFilter(filterPortion(id));

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

Filter parseFilter(const QString &input)
{
    QStringList fields = input.split(":");
    int columns = fields[0].toInt();

    Filter::matrixT matrix{};
    for (QString el : fields[1].split(","))
        matrix.append(el.toInt());

    QStringList anchorFields = fields[2].split(",");
    QPoint anchor{anchorFields[0].toInt(), anchorFields[1].toInt()};

    int divisor = fields[3].toInt();
    int offset = fields[4].toInt();

    return Filter{columns, matrix, anchor, divisor, offset};
}

ostream &operator<<(ostream &stream, const QString &string) {
    stream << string.toUtf8().data();
    return stream;
}
