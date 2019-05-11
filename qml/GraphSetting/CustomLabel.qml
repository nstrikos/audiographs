import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.2

import "../ButtonsRect"
import "../GraphRect"

Rectangle {

    property alias labelText: label.text

    width: definedWidth
    height: definedHeight
    Label {
        id: label
        //text: labelText
        font.pixelSize: 20
        anchors.verticalCenter: parent.verticalCenter
        Layout.minimumWidth: 150        
    }
}
