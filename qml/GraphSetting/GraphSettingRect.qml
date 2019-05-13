import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.2

import "../ButtonsRect"
import "../GraphRect"
import "../ParametersRect"

Rectangle {
    id: graphSettingRect

    property alias pointColorButton: pointColorButton
    property int definedHeight: graphSettingRect.height / 15
    property int definedWidth: graphSettingRect.width / 3

    visible: false
    anchors.fill: parent

    Grid {
        anchors.centerIn: parent
        columns: 2
        spacing: 10

        CustomLabel {
            labelText: qsTr("Point color")
        }

        CustomButton2 {
            id: pointColorButton
            width: definedWidth
            height: definedHeight
            color: myparameters.pointColor
            onPressed: {
                colorDialog.color = myparameters.pointColor
                colorDialog.request = "pointColorButton"
                colorDialog.open()
            }
        }

        CustomLabel {
            labelText: qsTr("Point size")
        }

        CustomSliderRect {
            id: pointSlider
            sliderValue: myparameters.pointSize
            onSliderValueChanged: myparameters.pointSize = sliderValue
        }

        CustomLabel {
            labelText: qsTr("Line color")
        }

        CustomButton2 {
            id: lineColorButton
            width: definedWidth
            height: definedHeight
            color: myparameters.lineColor
            onPressed: {
                colorDialog.color = myparameters.lineColor
                colorDialog.request = "lineColorButton"
                colorDialog.open()
            }
        }

        CustomLabel {
            labelText: qsTr("Line width")
        }

        CustomSliderRect {
            id: lineSlider
            sliderValue: myparameters.lineWidth
            onSliderValueChanged: myparameters.lineWidth = sliderValue
        }

        CustomLabel {
            labelText: qsTr("Highlight color")
        }

        CustomButton2 {
            id: highlightColorButton
            width: definedWidth
            height: definedHeight
            color: myparameters.highlightColor
            onPressed: {
                colorDialog.color = myparameters.highlightColor
                colorDialog.request = "highlightColorButton"
                colorDialog.open()
            }
        }

        CustomLabel {
            labelText: qsTr("Highlight size")
        }

        CustomSliderRect {
            id: highlightSlider
            sliderValue: myparameters.highlightSize
            maxValue: 40
            onSliderValueChanged: myparameters.highlightSize = sliderValue
        }

        CustomLabel {
            labelText: qsTr("Axes color")
        }

        CustomButton2 {
            id: axesColorButton
            width: definedWidth
            height: definedHeight
            color: myparameters.axesColor
            onPressed: {
                colorDialog.color = myparameters.axesColor
                colorDialog.request = "axesColorButton"
                colorDialog.open()
            }
        }

        CustomLabel {
            labelText: qsTr("Background color")
        }

        CustomButton2 {
            id: backgroundColorButton
            width: definedWidth
            height: definedHeight
            color: myparameters.backgroundColor
            onPressed: {
                colorDialog.color = myparameters.backgroundColor
                colorDialog.request = "backgroundColorButton"
                colorDialog.open()
            }
        }

        CustomLabel {
            labelText: qsTr("Show points")
        }

        CustomCheckButton {
            id: showPointsButton
            onPressed: {
                isPressed = !isPressed
                myparameters.showPoints = isPressed
            }
            Component.onCompleted: {
                isActive = false
                isPressed = myparameters.showPoints
            }
        }

        CustomLabel {
            labelText: qsTr("Show line")
        }

        CustomCheckButton {
            id: showLineButton
            onPressed: {
                isPressed = !isPressed
                myparameters.showLine = isPressed
            }
            Component.onCompleted: {
                isActive = false
                isPressed = myparameters.showLine
            }
        }

        Label {
            width: definedWidth
            height: definedHeight
        }

        CustomButton {
            id: restoreButton
            width: definedWidth
            height: definedHeight
            textSize: 20
            customText: qsTr("Restore defaults")
            onPressed: {
                myparameters.reset()
                pointColorButton.color = myparameters.pointColor
                pointSlider.sliderValue = myparameters.pointSize
                lineColorButton.color = myparameters.lineColor
                lineSlider.sliderValue = myparameters.lineWidth
                highlightColorButton.mycolor = myparameters.highlightColor
                highlightSlider.sliderValue = myparameters.highlightSize
                axesColorButton.mycolor = myparameters.axesColor
                backgroundColorButton.mycolor = myparameters.backgroundColor
            }
        }
    }

    ColorDialog {
        id: colorDialog

        property var request

        title: qsTr("Please choose a color")
        modality: Qt.WindowModal
        onAccepted: {
            if (request === "pointColorButton") {
                pointColorButton.color = color
                myparameters.pointColor = color
                pointColorButton.forceActiveFocus()
            }
            else if (request === "lineColorButton") {
                lineColorButton.color = color
                myparameters.lineColor = color
                lineColorButton.forceActiveFocus()
            }
            else if (request === "highlightColorButton") {
                highlightColorButton.color = color
                myparameters.highlightColor = color
                highlightColorButton.forceActiveFocus()
            }
            else if (request === "backgroundColorButton") {
                backgroundColorButton.color = color
                myparameters.backgroundColor = color
                backgroundColorButton.forceActiveFocus()
            }
            else if (request === "axesColorButton") {
                axesColorButton.color = color
                myparameters.axesColor = color
                axesColorButton.forceActiveFocus()
            }
        }

        onRejected: {
            if (request === "pointColorButton") {
                pointColorButton.forceActiveFocus()
            }
            else if (request === "lineColorButton") {
                lineColorButton.forceActiveFocus()
            }
            else if (request === "highlightColorButton") {
                highlightColorButton.forceActiveFocus()
            }
            else if (request === "backgroundColorButton") {
                backgroundColorButton.forceActiveFocus()
            }
            else if (request === "axesColorButton") {
                axesColorButton.forceActiveFocus()
            }
        }

    }

    function setFocus() {
        pointColorButton.forceActiveFocus()
    }

    focus: true
    Keys.onEscapePressed: escapePressed()
    Keys.onBackPressed: escapePressed()

    function escapePressed() {
        graphSettingRect.visible = false
        grid.visible = true
        grid.graphSettingsButton.forceActiveFocus()
    }
}
