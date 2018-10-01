#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "bluetoothconnector.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<BluetoothConnector>("QtCustom.WirelessDisk.BluetoothConnector", 1, 0, "BluetoothConnector");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
