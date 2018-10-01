#include <QTimer>

#include "bluetoothconnector.h"

BluetoothConnector::BluetoothConnector(QObject *parent) :
    QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol, parent)
{
    QBluetoothLocalDevice localDevice(this);
    if (localDevice.hostMode() == QBluetoothLocalDevice::HostPoweredOff)
    {
        localDevice.powerOn();
    }
}

BluetoothConnector::~BluetoothConnector()
{
}

void BluetoothConnector::establishConnection(const QString &btName)
{
    m_targetBluetoothName = btName;

    startDeviceDiscovery();
}

void BluetoothConnector::startDeviceDiscovery()
{
    QBluetoothDeviceDiscoveryAgent *discoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);

    connect(discoveryAgent, SIGNAL(deviceDiscovered(const QBluetoothDeviceInfo&)),
            this, SLOT(onDiscoveryAgentDeviceDiscovered(const QBluetoothDeviceInfo&)));
    connect(discoveryAgent, SIGNAL(error(QBluetoothDeviceDiscoveryAgent::Error)),
            this, SLOT(onDiscoveryAgentError(QBluetoothDeviceDiscoveryAgent::Error)));
    connect(discoveryAgent, SIGNAL(canceled()), this, SLOT(onDiscoveryAgentCanceled()));
    connect(discoveryAgent, SIGNAL(finished()), this, SLOT(onDiscoveryAgentFinished()));

    discoveryAgent->start();
}

void BluetoothConnector::onDiscoveryAgentDeviceDiscovered(const QBluetoothDeviceInfo &info)
{
    QBluetoothDeviceDiscoveryAgent *discoveryAgent = (QBluetoothDeviceDiscoveryAgent*)(this->sender());
    if (info.name() == m_targetBluetoothName)
    {
        /* Delete discovery agent after target device is found. */
        discoveryAgent->stop();
        discoveryAgent->deleteLater();

        /* Car wireless audio repeator have be found */
        emit cwarDiscovered(info.name(), info.address().toString());

        /* Connect with target device after it be found. */
        connect(this, SIGNAL(connected()), this, SLOT(onBluetoothSocketConnected()));
        connect(this, SIGNAL(error(QBluetoothSocket::SocketError)),
                this, SLOT(onBluetoothSocketError(QBluetoothSocket::SocketError)));
        connectToService(info.address(), info.deviceUuid());
    }
}

void BluetoothConnector::onDiscoveryAgentError(QBluetoothDeviceDiscoveryAgent::Error error)
{
    QBluetoothDeviceDiscoveryAgent *discoveryAgent = (QBluetoothDeviceDiscoveryAgent*)(this->sender());
    QString errStr;

    qDebug() << "->> " << " Discovery Error: " << error << ", " << discoveryAgent->errorString();
    switch (error)
    {
    case QBluetoothDeviceDiscoveryAgent::PoweredOffError: errStr = tr("与设备建立连接时，蓝牙被关闭"); break;
    case QBluetoothDeviceDiscoveryAgent::NoError: errStr = tr("未发生错误"); break;

    default: errStr = tr("与设备建立连接发生了未知的错误"); break;
    }

    /* Delete discovery agent after error occurred */
    discoveryAgent->stop();
    discoveryAgent->deleteLater();
    emit this->errorOccured(errStr);
    emit this->errorOccured(QString("error: ") + QString::number(error) + tr(", ") + discoveryAgent->errorString());
}

void BluetoothConnector::onDiscoveryAgentCanceled()
{
    QString errStr = tr("与设备建立连接失败，被取消");
    emit this->errorOccured(errStr);
}

void BluetoothConnector::onDiscoveryAgentFinished()
{
    QString errStr = tr("与设备建立连接超时，未搜索到设备");
    emit this->errorOccured(errStr);
}

void BluetoothConnector::onBluetoothSocketConnected()
{
    //debug
    emit this->errorOccured(tr("Socket connected."));
    write("Hello world. This message send by bluetooth.\r\n");
}

void BluetoothConnector::onBluetoothSocketError(QBluetoothSocket::SocketError error)
{
    QBluetoothSocket *socket = (QBluetoothSocket*)(sender());
    QString errStr;

    qDebug() << "->> " << "Discovery Error: " << error << ", " << socket->errorString();
    errStr = tr("与设备建立连接时发生了错误");
    emit this->errorOccured(errStr);
    emit this->errorOccured(QString("error: ") + QString::number(error) + tr(", ") + socket->errorString());
    emit this->errorOccured(QString("Socket state: ") + QString::number(socket->state()));

    //socket->deleteLater();
}
