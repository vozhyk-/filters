#ifndef FILTERED_IMAGE_PROVIDER_HPP
#define FILTERED_IMAGE_PROVIDER_HPP

#include <QQuickImageProvider>

class FilteredImageProvider : public QQuickImageProvider
{
public:
    FilteredImageProvider() : QQuickImageProvider{QQuickImageProvider::Image}
    {
    }

    QImage requestImage(
        const QString &id, QSize *size, const QSize &requestedSize) override;
};

#endif // FILTERED_IMAGE_PROVIDER_HPP
