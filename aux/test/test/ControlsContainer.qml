import QtQuick 2.5
import QtQuick.Controls 1.4

Rectangle {
    id: controlsContainer

    property alias xStart: textInputXStart.value
    property alias xEnd: textInputXEnd.value
    property alias yStart: textInputYStart.value
    property alias yEnd: textInputYEnd.value
    property alias drawLinesEnabled: checkboxDrawLine.checked

    anchors {
        top: parent.top
        bottom: parent.bottom
        left: parent.left
    }
    width: 250
    border.color: "black"

    Column {
        anchors.fill: parent
        spacing: 5

        TextInputFrame {
            id: textInputFrame
        }

        TextInputFrame {
            id: textInputXStart
            text: "-50"
        }

        TextInputFrame {
            id: textInputXEnd
            text: "50"
        }

        TextInputFrame {
            id: textInputYStart
            text: "-50"
        }

        TextInputFrame {
            id: textInputYEnd
            text: "100"
        }
        CheckBox {
            id: checkboxDrawLine
            text: "Draw line"
            checked: false
        }
    }
}
