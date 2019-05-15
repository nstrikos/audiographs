import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5

import "../js/ButtonFunctions.js" as ButtonFunctions

Button {
    id: root
    width: parent.width
    property bool isActive: false
    property bool isPressed: false
    property int textSize: 25
    property alias color: rect.color
    property string customText

    Accessible.name: "My button"

    contentItem: Text {
        id: buttonText
        text: customText
        font.pixelSize: textSize
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors.fill: parent
        antialiasing: true
    }

    background: Rectangle {
        id: rect
        implicitHeight: 100
        radius: 10
        border.color: ButtonFunctions.setBorderColor()
        border.width: 5
    }

    onFocusChanged: ButtonFunctions.focusChanged()
}
