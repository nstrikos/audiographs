import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

Rectangle {
    id: root

    property alias functionInput: functionInput
    property alias functionText: functionInput.text
    property alias minimumXText: startXInput.text
    property alias maximumXText: endXInput.text
    property alias stepText: stepInput.text
    property alias checkDrawLine: checkDrawLine

    color: "white"
    anchors.fill: parent
    visible: false

    Column {
        id: column
        spacing: 15
        anchors.fill: parent

        TextEditLayout {
            id: functionInput
            labelText: qsTr("Function:")
            input.text: "sin(x)"
            KeyNavigation.tab: startXInput
        }

        TextEditLayout {
            id: startXInput
            labelText: qsTr("Start at:")
            input.text: "-10"
            KeyNavigation.tab: endXInput
        }

        TextEditLayout {
            id: endXInput
            labelText: qsTr("End at:")
            input.text: "10"
            KeyNavigation.tab: minimumYInput
        }

        TextEditLayout {
            id: minimumYInput
            labelText: qsTr("Minimum Y:")
            input.text: "-10"
            KeyNavigation.tab: maximumYInput
        }

        TextEditLayout {
            id: maximumYInput
            labelText: qsTr("Maximum Y:")
            input.text: "10"
            KeyNavigation.tab: stepInput
        }

        TextEditLayout {
            id: stepInput
            labelText: qsTr("Step:")
            input.text: "100"
            KeyNavigation.tab: checkDrawLine
        }

        CheckButton {
            id: checkDrawLine
            text: qsTr("Draw lines")
            KeyNavigation.tab: functionInput
        }
    }

    function forceActiveFocus() {
        functionInput.forceActiveFocus()
    }

    function escapePressed() {
        parametersRect.visible = false
        grid.visible = true
        grid.parametersButton.forceActiveFocus()
    }
}
