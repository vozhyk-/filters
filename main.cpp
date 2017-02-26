#include <QApplication>
#include <QQmlApplicationEngine>

#include "FilteredImageProvider.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine{};
    engine.addImageProvider("filtered", new FilteredImageProvider{});
    engine.load("app.qml");

    return app.exec();
}
