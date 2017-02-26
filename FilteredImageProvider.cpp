#include "FilteredImageProvider.hpp"

#include "Filter.hpp"

QString imagePathPortion(const QString &id);
QString filterPortion(const QString &id);
Filter parseFilter(const QString &input);

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
    QString url = id.section(';', 1);
    return QUrl::fromUserInput(url).toLocalFile();
}

QString filterPortion(const QString &id)
{
    return id.section(';', 0);
}

Filter parseFilter(const QString &input)
{
    QStringList fields = input.split(":");
    int columns = fields[0].toInt();

    Filter::matrixT matrix{};
    for (QString el : fields[1].split(","))
        matrix.append(el.toDouble());

    int divisor = fields[2].toInt();

    return Filter{columns, matrix, divisor};
}
