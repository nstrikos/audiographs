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
    property int clearButtonWidth: 100

    color: "white"
    anchors.fill: parent
    visible: false

    //Column

    Flickable {
        id: flickable
        anchors.fill: parent
        contentHeight: grid.height + 75

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

            CustomButton {
                id: clearFunctionButton
                onPressed: functionInput.input.text = ""
            }

            TextEditLayout {
                id: startXInput
                labelText: qsTr("Start at:")
                input.text: "-10"
                KeyNavigation.tab: clearStartButton
                //Accessible.name: text
            }

            CustomButton {
                id: clearStartButton
                width: clearButtonWidth
                onPressed: startXInput.input.text = ""
                KeyNavigation.tab: endXInput
                //Accessible.name: text + " " + qsTr("start")
            }

            TextEditLayout {
                id: endXInput
                labelText: qsTr("End at:")
                input.text: "10"
                KeyNavigation.tab: clearEndButton
            }

            CustomButton {
                id: clearEndButton
                width: clearButtonWidth
                onPressed: {
                    endXInput.input.text = ""
                }
                KeyNavigation.tab: minimumYInput
//                Accessible.name: text + " " + qsTr("end")
            }

            TextEditLayout {
                id: minimumYInput
                labelText: qsTr("Minimum Y:")
                input.text: "-10"
                KeyNavigation.tab: clearMinimumButton
            }

            CustomButton {
                id: clearMinimumButton
                text: qsTr("Clear")
                width: clearButtonWidth
                onPressed: {
                    minimumYInput.input.text = ""
                }
                KeyNavigation.tab: maximumYInput
//                Accessible.name: text + " " + qsTr(" minimum")
            }

            TextEditLayout {
                id: maximumYInput
                labelText: qsTr("Maximum Y:")
                input.text: "10"
                KeyNavigation.tab: clearMaximumButton
            }

            CustomButton {
                id: clearMaximumButton
                text: qsTr("Clear")
                width: clearButtonWidth
                onPressed: {
                    maximumYInput.input.text = ""
                }
                KeyNavigation.tab: stepInput
//                Accessible.name: text + " " + qsTr("maximum")
            }

            TextEditLayout {
                id: stepInput
                labelText: qsTr("Step:")
                input.text: "100"
                KeyNavigation.tab: clearPointsButton
            }

            CustomButton {
                id: clearPointsButton
                text: qsTr("Clear")
                width: clearButtonWidth
                onPressed: {
                    stepInput.input.text = ""
                }
                KeyNavigation.tab: functionInput
//                Accessible.name: text + " " + qsTr("number of points")
            }
        }
    }

    function forceActiveFocus() {
        flickable.contentY = 0
        functionInput.forceActiveFocus()
    }

    function escapePressed() {
        parametersRect.visible = false
        grid.visible = true
        grid.parametersButton.forceActiveFocus()
    }
}
