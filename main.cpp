#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickImageProvider>

class FilteredImageProvider : public QQuickImageProvider
{
public:
    FilteredImageProvider() : QQuickImageProvider{QQuickImageProvider::Image}
    {
    }

    QImage requestImage(
        const QString &id, QSize *size, const QSize &requestedSize)
    {
        Q_UNUSED(id);
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
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine{};
    engine.addImageProvider("filtered", new FilteredImageProvider{});
    engine.load("app.qml");

    return app.exec();
}
