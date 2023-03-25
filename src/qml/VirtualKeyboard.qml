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
        button1.forceActiveFocus()
    }

    Rectangle {
        anchors.fill: parent
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

        Button {
            id: button1
            text: "1"
            onClicked: expression += "1"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "2"
            onClicked: expression += "2"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "3"
            onClicked: expression += "3"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "4"
            onClicked: expression += "4"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "5"
            onClicked: expression += "5"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "6"
            onClicked: expression += "6"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "7"
            onClicked: expression += "7"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "8"
            onClicked: expression += "8"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "9"
            onClicked: expression += "9"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "0"
            onClicked: expression += "0"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "+"
            onClicked: expression += "+"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "-"
            onClicked: expression += "-"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "*"
            onClicked: expression += "*"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "/"
            onClicked: expression += "/"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "("
            onClicked: expression += "("
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: ")"
            onClicked: expression += ")"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "^"
            onClicked: expression += "^"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "."
            onClicked: expression += "."
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: ","
            onClicked: expression += ","
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "%"
            onClicked: expression += "%"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "q"
            onClicked: expression += "q"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "w"
            onClicked: expression += "w"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "e"
            onClicked: expression += "e"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "r"
            onClicked: expression += "r"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "t"
            onClicked: expression += "t"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "y"
            onClicked: expression += "y"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "u"
            onClicked: expression += "u"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "i"
            onClicked: expression += "i"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "o"
            onClicked: expression += "o"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "p"
            onClicked: expression += "p"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "a"
            onClicked: expression += "a"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "s"
            onClicked: expression += "s"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "d"
            onClicked: expression += "d"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "f"
            onClicked: expression += "f"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "g"
            onClicked: expression += "g"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "h"
            onClicked: expression += "h"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "j"
            onClicked: expression += "j"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "k"
            onClicked: expression += "k"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "l"
            onClicked: expression += "l"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "z"
            onClicked: expression += "z"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "x"
            onClicked: expression += "x"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "c"
            onClicked: expression += "c"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "v"
            onClicked: expression += "v"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "b"
            onClicked: expression += "b"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "n"
            onClicked: expression += "n"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "m"
            onClicked: expression += "m"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "clear"
            Layout.columnSpan: 2
            onClicked: expression = ""
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "OK"
            Layout.columnSpan: 2
            onClicked: {
                virtualKeyboard.visible = false
                window.keyboard(expression)
            }
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
