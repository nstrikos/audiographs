import QtQuick 2.9
import QtQuick.Controls 1.4

Rectangle {
    id: controlsContainer

    signal graphButtonPressed()

    property alias inputFunction: functionRect.text
    property alias xStart: minimumXRect.value
    property alias xEnd: maximumXRect.value
    property alias yStart: minimumYRect.value
    property alias yEnd: maximumYRect.value
    property alias h: intervalRect.value
    property alias firstInputText: functionRect.inputText

    property alias drawLinesEnabled: checkboxDrawLine.checked

    Column {
        id: column
        spacing: 5
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
        InputRect {
            id: functionRect
            labelText: "Function:"
            accessibleDescription: "Function"
            text: "sin(x)"
            KeyNavigation.tab: minimumXRect.inputText
        }
        InputRect {
            id: minimumXRect
            labelText: "Minimum x:"
            accessibleDescription: "Minimum x"
            text: "-10"
            KeyNavigation.tab: maximumXRect.inputText
        }
        InputRect {
            id: maximumXRect
            labelText: "Maximum x:"
            text: "10"
            accessibleDescription: "Maximum x"
            KeyNavigation.tab: minimumYRect.inputText
        }
        InputRect {
            id: minimumYRect
            labelText: "Minimum y:"
            text: "-10"
            accessibleDescription: "Minimum y"
            KeyNavigation.tab: maximumYRect.inputText
        }
        InputRect {
            id: maximumYRect
            labelText: "Maximum y:"
            text: "10"
            accessibleDescription: "Maximum y"
            KeyNavigation.tab: intervalRect.inputText
        }
        InputRect {
            id: intervalRect
            labelText: "x interval:"
            text: "0.1"
            accessibleDescription: "x interval"
            KeyNavigation.tab: checkboxDrawLine
        }
        CheckBox {
            id: checkboxDrawLine
            text: "Draw line"
            checked: false
            KeyNavigation.tab: graphButton
            height: 60
            //width: parent.width
        }
    }
    Button {
        id: graphButton
        anchors.top: column.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 10
        text: "Plot function"
        onClicked: graphButtonPressed()
        Accessible.role: Accessible.Button
        Accessible.name: text
        Accessible.description: text
    }
}

