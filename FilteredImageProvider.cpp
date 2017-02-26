#include "FilteredImageProvider.hpp"

QString originalImagePath(const QString &id);

QImage FilteredImageProvider::requestImage(
    const QString &id, QSize *size, const QSize &requestedSize)
{
    Q_UNUSED(size);
    Q_UNUSED(requestedSize);

    QImage original{originalImagePath(id)};

    return original;
}

QString originalImagePath(const QString &id)
{
    QString url = id.section(';', 1);
    return QUrl::fromUserInput(url).toLocalFile();
}
