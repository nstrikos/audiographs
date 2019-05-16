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
    property int clearButtonWidth: 200


    color: "white"
    anchors.fill: parent
    visible: false

    //Column
    Grid {
        id: column
        columns: 2
        spacing: 15
        anchors.fill: parent

        TextEditLayout {
            id: functionInput
            labelText: qsTr("Function:")
            input.text: "sin(x)"
            KeyNavigation.tab: clearFunctionButton
        }

        RoundButton {
            id: clearFunctionButton
            text: qsTr("Clear function")
            width: clearButtonWidth
            onPressed: {
                functionInput.input.text = ""
            }
            KeyNavigation.tab: startXInput
            Accessible.name: text
        }

        TextEditLayout {
            id: startXInput
            labelText: qsTr("Start at:")
            input.text: "-10"
            KeyNavigation.tab: clearStartButton
            Accessible.name: text
        }

        RoundButton {
            id: clearStartButton
            text: qsTr("Clear start")
            width: clearButtonWidth
            onPressed: startXInput.input.text = ""
            KeyNavigation.tab: endXInput
            Accessible.name: text
        }

        TextEditLayout {
            id: endXInput
            labelText: qsTr("End at:")
            input.text: "10"
            KeyNavigation.tab: clearEndButton
        }

        RoundButton {
            id: clearEndButton
            text: qsTr("Clear end")
            width: clearButtonWidth
            onPressed: {
                endXInput.input.text = ""
            }
            KeyNavigation.tab: minimumYInput
            Accessible.name: text
        }

        TextEditLayout {
            id: minimumYInput
            labelText: qsTr("Minimum Y:")
            input.text: "-10"
            KeyNavigation.tab: clearMinimumButton
        }

        RoundButton {
            id: clearMinimumButton
            text: qsTr("Clear minimum")
            width: clearButtonWidth
            onPressed: {
                minimumYInput.input.text = ""
            }
            KeyNavigation.tab: maximumYInput
            Accessible.name: text
        }

        TextEditLayout {
            id: maximumYInput
            labelText: qsTr("Maximum Y:")
            input.text: "10"
            KeyNavigation.tab: clearMaximumButton
        }

        RoundButton {
            id: clearMaximumButton
            text: qsTr("Clear maximum")
            width: clearButtonWidth
            onPressed: {
                maximumYInput.input.text = ""
            }
            KeyNavigation.tab: stepInput
            Accessible.name: text
        }

        TextEditLayout {
            id: stepInput
            labelText: qsTr("Step:")
            input.text: "100"
            KeyNavigation.tab: clearPointsButton
        }

        RoundButton {
            id: clearPointsButton
            text: qsTr("Clear number of points")
            width: clearButtonWidth
            onPressed: {
                stepInput.input.text = ""
            }
            KeyNavigation.tab: functionInput
            Accessible.name: text
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
