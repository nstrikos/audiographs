import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

RowLayout {

    property alias text: input.text
    property alias labelText: label.text
    property alias input: input
    property alias minimumWidth: rect.minimumWidth

    width: parent.width

    Rectangle {
        id: rect
        property int minimumWidth: 150
        Layout.minimumWidth: minimumWidth
        Label {
            id: label
            text: labelText
            font.pixelSize: 20
            anchors.centerIn: parent
        }
    }

    Rectangle {
        id: textRect
        border.color: "gray"
        border.width: 2
        radius: 10
        Layout.fillWidth: true
        Layout.preferredHeight: 50
        Accessible.name: "test button"

        TextInput {
            id: input
            text: text
            horizontalAlignment: TextInput.AlignHCenter
            focus: true
            clip: true
            anchors.centerIn: parent
            font.pixelSize: 20
            width: parent.width
            onActiveFocusChanged: {
                if (activeFocus) {
                    textRect.border.color = "red"
                    textRect.border.width = 5
                    if (window.talkSpeech)
                        texttospeech.speak(label.text + input.text)
                }
                else {
                    textRect.border.color = "gray"
                    textRect.border.width = 2
                }
            }

            Keys.onEscapePressed: {
                parametersRect.escapePressed()
              }

            Keys.onBackPressed: {
                parametersRect.escapePressed()
            }
        }
    }

    onFocusChanged: {
        if (activeFocus)
            input.forceActiveFocus()
    }
}
