import QtQuick 2.9
import QtQuick.Window 2.2

import QtCustom.WirelessDisk.BluetoothConnector 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    BluetoothConnector {
        id: bluetoothConnector

        onErrorOccured: log(errorString)
        onCwarDiscovered: {
            log(qsTr("已找到无线磁盘设备，建立连接中"))
            log("->> " + bluetoothName + ", " + bluetoothAddress)
        }
        onConnected: log(qsTr("已连接到无线磁盘设备"))
    }

    ListModel {
        id: listModel
    }

    ListView {
        id: listView
        anchors.fill: parent

        model: listModel
        delegate: Text {
            text: name
        }
    }

    Component.onCompleted: {
        log(qsTr("<? Car Wireless Audio Repeator ?>"))
        log(qsTr("连接车载无线音频中继器中..."))
        bluetoothConnector.establishConnection("BT_Lanlan")
    }

    function log(nameStr) {
        listModel.append({name: nameStr})
    }
}
