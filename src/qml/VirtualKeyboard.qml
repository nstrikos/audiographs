import QtQuick 2.12
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

Item {
    property string expression: ""
    width: 800
    height: 400
    visible: false

    function init()
    {
        window.disableShortcuts()
        button1.forceActiveFocus()
    }

    function addX()
    {
        expression += "x"
        textToSpeech.speak("x")
    }

    function backspace()
    {
        expression = expression.slice(0, -1)
        textToSpeech.speak(expression)
    }

    Rectangle {
        anchors.fill: parent
    }

    Keys.onPressed: {
        if (event.key === Qt.Key_Return) {
            event.accepted = true;
            console.log("return pressed", expression)
            virtualKeyboard.visible = false
            window.keyboard(expression)
            window.enableShortcuts()
        }
    }
    Rectangle {
        id: rect
        anchors.top: parent.top
        width: parent.width
        height: 50
        //anchors.topMargin: 50
        color: "white"
        TextInput {
            id: textEdit
            anchors.fill: parent
            readOnly: true
            Text {
                text: expression
                font.family: "Helvetica"
                font.pointSize: 24
            }
        }
    }

    GridLayout {
        id: grid
        rows: 3
        columns: 10
        anchors.top: rect.bottom
        anchors.bottom: parent.bottom
        width: parent.width

        VirtualKeyboardButton {
            id: button1
            text: "x"
        }

        VirtualKeyboardButton {
            text: "+"            
        }

        Button {
            text: "-"
            onPressed: {
                expression += text
                textToSpeech.speak(qsTr("minus"))
            }
            Layout.fillWidth: true
            Layout.fillHeight: true
            onFocusChanged: {
                if (activeFocus)
                    textToSpeech.speak(qsTr("minus"))
            }
        }

        VirtualKeyboardButton {
            text: "*"            
        }

        VirtualKeyboardButton {
            text: "/"
        }

        VirtualKeyboardButton {
            text: "("
        }

        VirtualKeyboardButton {
            text: ")"
        }

        VirtualKeyboardButton {
            text: "^"
        }

        VirtualKeyboardButton {
            text: "."
        }

        VirtualKeyboardButton {
            text: ","
        }

        VirtualKeyboardButton {
            text: "1"
        }

        VirtualKeyboardButton {
            text: "2"
        }

        VirtualKeyboardButton {
            text: "3"
        }

        VirtualKeyboardButton {
            text: "4"
        }

        VirtualKeyboardButton {
            text: "5"
        }

        VirtualKeyboardButton {
            text: "6"
        }

        VirtualKeyboardButton {
            text: "7"
        }

        VirtualKeyboardButton {
            text: "8"
        }

        VirtualKeyboardButton {
            text: "9"
        }

        VirtualKeyboardButton {
            text: "0"
        }

        VirtualKeyboardButton {
            text: "a"
        }

        VirtualKeyboardButton {
            text: "b"
        }

        VirtualKeyboardButton {
            text: "c"
        }

        VirtualKeyboardButton {
            text: "d"
        }

        VirtualKeyboardButton {
            text: "e"
        }

        VirtualKeyboardButton {
            text: "f"
        }

        VirtualKeyboardButton {
            text: "g"
        }

        VirtualKeyboardButton {
            text: "h"
        }

        VirtualKeyboardButton {
            text: "i"
        }

        VirtualKeyboardButton {
            text: "j"
        }

        VirtualKeyboardButton {
            text: "k"
        }

        VirtualKeyboardButton {
            text: "l"
        }

        VirtualKeyboardButton {
            text: "m"
        }

        VirtualKeyboardButton {
            text: "n"
        }

        VirtualKeyboardButton {
            text: "o"
        }

        VirtualKeyboardButton {
            text: "p"
        }

        VirtualKeyboardButton {
            text: "q"
        }

        VirtualKeyboardButton {
            text: "r"
        }

        VirtualKeyboardButton {
            text: "s"
        }

        VirtualKeyboardButton {
            text: "t"
        }

        VirtualKeyboardButton {
            text: "u"
        }

        VirtualKeyboardButton {
            text: "v"
        }

        VirtualKeyboardButton {
            text: "w"
        }

        VirtualKeyboardButton {
            text: "x"
        }

        VirtualKeyboardButton {
            text: "y"
        }

        VirtualKeyboardButton {
            text: "z"
        }

        Button {
            text: "Backspace"
            Layout.columnSpan: 2
            onPressed: backspace()
            onFocusChanged: {
                if (activeFocus)
                    textToSpeech.speak(qsTr("Backspace"))
            }
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        VirtualKeyboardButton {
            text: "Clear"
            Layout.columnSpan: 2
            onPressed: expression = ""
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "OK"
            Layout.columnSpan: 2
            onPressed: {
                virtualKeyboard.visible = false
                window.keyboard(expression)
                window.enableShortcuts()
            }
            onFocusChanged: {
                if (activeFocus)
                    textToSpeech.speak(qsTr("OK"))
            }
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
