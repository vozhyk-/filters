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
    int columns = input.section(":", 0, 0).toInt();

    QVector<double> matrix{};
    for (QString el : input.section(":", 1).split(","))
        matrix.append(el.toDouble());

    return Filter{columns, matrix};
}
