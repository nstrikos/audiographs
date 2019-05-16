import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5

import "../js/ButtonFunctions.js" as ButtonFunctions

Button {
    id: root
    width: parent.width
    property bool isActive: false
    property bool isPressed: false
    property string customText: "Text"
    property int textSize: 25

    Accessible.name: buttonText.text

    contentItem: Text {
        id: buttonText
        text: customText
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: textSize
        anchors.fill: parent
        antialiasing: true
    }

    background: Rectangle {
        implicitHeight: 100
        radius: 10
        border.color: ButtonFunctions.setBorderColor()
        color: isActive ? "lightblue": "white"
        border.width: 5
    }

    onFocusChanged:  {
        if (activeFocus) {
            isActive = true
            //androidClient.speak(buttonText.text)
            //androidClient.vibrate("500")
            if (window.talkSpeech)
                texttospeech.speak(buttonText.text)
        }
        else {
            isActive = false
        }
    }

}

