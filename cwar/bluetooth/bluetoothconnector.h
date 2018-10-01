#ifndef BLUETOOTHCONNECTOR_H
#define BLUETOOTHCONNECTOR_H

#include <QObject>
#include <QtBluetooth/qtbluetoothglobal.h>
#include <QtBluetooth/qbluetoothlocaldevice.h>
#include <QtBluetooth/qbluetoothaddress.h>
#include <QtBluetooth/qbluetoothdevicediscoveryagent.h>
#include <QtBluetooth/qbluetoothsocket.h>

class BluetoothConnector : public QBluetoothSocket
{
    Q_OBJECT
public:
    explicit BluetoothConnector(QObject *parent = nullptr);
    virtual ~BluetoothConnector(void);

    Q_INVOKABLE void establishConnection(const QString &btName);

protected:
    void startDeviceDiscovery(void);

signals:
    void errorOccured(const QString &errorString);
    void cwarDiscovered(const QString &bluetoothName, const QString &bluetoothAddress);

public slots:

private slots:
    /* This functions for discovery service */
    void onDiscoveryAgentDeviceDiscovered(const QBluetoothDeviceInfo &info);
    void onDiscoveryAgentError(QBluetoothDeviceDiscoveryAgent::Error error);
    void onDiscoveryAgentCanceled(void);
    void onDiscoveryAgentFinished(void);

    /* This functions for BT socket */
    void onBluetoothSocketConnected(void);
    void onBluetoothSocketError(QBluetoothSocket::SocketError error);

private:
    QString                         m_targetBluetoothName;
    QBluetoothDeviceDiscoveryAgent  *m_discoveryAgent;
};

#endif // BLUETOOTHCONNECTOR_H
