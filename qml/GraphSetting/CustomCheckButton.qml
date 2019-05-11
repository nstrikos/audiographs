import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.2

import "../ButtonsRect"
import "../GraphRect"
import "../ParametersRect"

Button {
    id: showPointsButton
    
    //property alias text: label.text
    property bool isActive: false
    property bool isPressed: false
    
    height: definedHeight
    width: definedWidth
    
    contentItem: Text {
        id: buttonText
        text: showPointsButton.isPressed ? "On" : "Off"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 20
        anchors.fill: parent
        antialiasing: true
    }
    
    background: Rectangle {
        implicitHeight: 50
        radius: 10
        border.color: showPointsButton.isActive ? "red" : "gray"
        color: showPointsButton.isPressed ? "lightblue": "lightgray"
        border.width: 5//showPointsButton.isActive ? 5 : 2
    }
    
    onFocusChanged: {
        if (activeFocus) {
            isActive = true
            speak()
        }
        else {
            isActive = false
        }
    }
}
