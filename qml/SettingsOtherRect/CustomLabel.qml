import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

Rectangle {

    property alias labelText: label.text

    width: 150
    height: 100
    Label {
        id: label
        font.pixelSize: 20
        anchors.verticalCenter: parent.verticalCenter
        Layout.minimumWidth: 150
    }
}
