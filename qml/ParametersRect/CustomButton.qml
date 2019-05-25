import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

Button {
    id: button

    property bool isActive: false
    property bool isPressed: false

    text: qsTr("Clear")
    width: clearButtonWidth

    font.pixelSize: 20

    KeyNavigation.tab: startXInput
    Accessible.name: text

    background: Rectangle {
        implicitHeight: 50
        radius: 10
        border.color: {
            if (button.isActive)
                return "red"
            else
                return "gray"
        }
        color: button.isActive ? "lightblue": "white"
        border.width: 5
    }

    onFocusChanged:     if (activeFocus) {
                            isActive = true
                            if (window.talkSpeech)
                                texttospeech.speak(button.text)
                        }
                        else {
                            isActive = false
                        }

    Keys.onEscapePressed: parametersRect.escapePressed()
    Keys.onBackPressed: parametersRect.escapePressed()
}
