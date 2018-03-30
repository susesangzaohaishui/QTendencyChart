#include <QApplication>
#include <QQmlApplicationEngine>
#include "testwidget.h"
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

//    QQmlApplicationEngine engine;
//    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
//    if (engine.rootObjects().isEmpty())
//        return -1;
    TEstWidget widget;
    widget.show();
    qDebug()<<10 %4320;
    return app.exec();
}
