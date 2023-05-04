import QtQuick 2.12
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

Item {
    id: virtualNumericalKeyboard
    property string expression: ""
    property string target: ""
    width: 800
    height: 400
    visible: false

    function init(text, control)
    {
        button1.forceActiveFocus()
        target = control
        expression = text
    }

    Rectangle {
        anchors.fill: parent
    }

    Rectangle {
        id: rect
        anchors.top: parent.top
        width: parent.width
        height: 50
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
        rows: 1
        columns: 10
        anchors.top: rect.bottom
        anchors.bottom: parent.bottom
        width: parent.width

        Button {
            id: button1
            text: "1"
            onPressed: expression += "1"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "2"
            onPressed: expression += "2"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "3"
            onPressed: expression += "3"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "4"
            onPressed: expression += "4"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "5"
            onPressed: expression += "5"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "6"
            onPressed: expression += "6"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "7"
            onPressed: expression += "7"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "8"
            onPressed: expression += "8"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "9"
            onPressed: expression += "9"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "0"
            onPressed: expression += "0"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "-"
            onPressed: expression += "-"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "."
            onPressed: expression += "."
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "clear"
            Layout.columnSpan: 2
            onPressed: expression = ""
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: "OK"
            Layout.columnSpan: 2
            onPressed: {
                virtualNumericalKeyboard.visible = false
                window.numericalKeyboard(expression, target)
            }
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
