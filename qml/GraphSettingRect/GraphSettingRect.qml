import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.2

Rectangle {
    id: graphSettingRect

    property alias pointColorButton: pointColorButton
    property int definedHeight: 50//graphSettingRect.height / 15
    property int definedWidth: graphSettingRect.width - pointColorLabel.width - 10//graphSettingRect.width / 5
    property int gridHeight

    visible: false
    anchors.fill: parent

    Flickable {
        id: flickable
        anchors.fill: parent
        contentHeight: 11 * 60

        Grid {
            //id: grid
            //anchors.centerIn: parent
            anchors.fill: parent
            columns: 2
            spacing: 10

            CustomLabel {
                id: pointColorLabel
                labelText: qsTr("Point color")
            }

            CustomButton {
                id: pointColorButton
                width: graphSettingRect.width - pointColorLabel.width - 10//definedWidth
                height: definedHeight
                color: myparameters.pointColor
                customText: pointColorLabel.labelText
                //Layout.fillWidth: true
                onPressed: {
                    colorDialog.color = myparameters.pointColor
                    colorDialog.request = "pointColorButton"
                    colorDialog.open()
                }
            }

            CustomLabel {
                id: pointSizeLabel
                labelText: qsTr("Point size")
            }

            CustomSliderRect {
                id: pointSlider
                width: graphSettingRect.width - pointColorLabel.width - 10
                text: pointSizeLabel.labelText
                sliderValue: myparameters.pointSize
                onSliderValueChanged: myparameters.pointSize = sliderValue
            }

            CustomLabel {
                id: lineColorLabel
                labelText: qsTr("Line color")
            }

            CustomButton {
                id: lineColorButton
                width: graphSettingRect.width - pointColorLabel.width - 10
                height: definedHeight
                color: myparameters.lineColor
                customText: lineColorLabel.labelText
                onPressed: {
                    colorDialog.color = myparameters.lineColor
                    colorDialog.request = "lineColorButton"
                    colorDialog.open()
                }
            }

            CustomLabel {
                id: lineWidthLabel
                labelText: qsTr("Line width")
            }

            CustomSliderRect {
                id: lineSlider
                width: graphSettingRect.width - pointColorLabel.width - 10
                sliderValue: myparameters.lineWidth
                text: lineWidthLabel.labelText
                onSliderValueChanged: myparameters.lineWidth = sliderValue
            }

            CustomLabel {
                id: highlightColorLabel
                labelText: qsTr("Highlight color")
            }

            CustomButton {
                id: highlightColorButton
                width: graphSettingRect.width - pointColorLabel.width - 10
                height: definedHeight
                color: myparameters.highlightColor
                customText: highlightColorLabel.labelText
                onPressed: {
                    colorDialog.color = myparameters.highlightColor
                    colorDialog.request = "highlightColorButton"
                    colorDialog.open()
                }
            }

            CustomLabel {
                id: highlightSizeLabel
                labelText: qsTr("Highlight size")
            }

            CustomSliderRect {
                id: highlightSlider
                width: graphSettingRect.width - pointColorLabel.width - 10
                sliderValue: myparameters.highlightSize
                text: highlightSizeLabel.labelText
                maxValue: 40
                onSliderValueChanged: myparameters.highlightSize = sliderValue
            }

            CustomLabel {
                id: axesColorLabel
                labelText: qsTr("Axes color")
            }

            CustomButton {
                id: axesColorButton
                width: graphSettingRect.width - pointColorLabel.width - 10
                height: definedHeight
                color: myparameters.axesColor
                customText: axesColorLabel.labelText
                onPressed: {
                    colorDialog.color = myparameters.axesColor
                    colorDialog.request = "axesColorButton"
                    colorDialog.open()
                }
            }

            CustomLabel {
                id: backgroundColorLabel
                labelText: qsTr("Background color")
            }

            CustomButton {
                id: backgroundColorButton
                width: graphSettingRect.width - pointColorLabel.width - 10
                height: definedHeight
                color: myparameters.backgroundColor
                customText: backgroundColorLabel.labelText
                onPressed: {
                    colorDialog.color = myparameters.backgroundColor
                    colorDialog.request = "backgroundColorButton"
                    colorDialog.open()
                }
            }

            CustomLabel {
                id: showPointsLabel
                labelText: qsTr("Show points")
            }

            CustomCheckButton {
                id: showPointsButton
                width: graphSettingRect.width - pointColorLabel.width - 10
                labelText: showPointsLabel.labelText
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
                id: showLineLabel
                labelText: qsTr("Show line")
            }

            CustomCheckButton {
                id: showLineButton
                width: graphSettingRect.width - pointColorLabel.width - 10
                labelText: showLineLabel.labelText
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
                width: 180//definedWidth
                height: 50//definedHeight
            }

            CustomButton {
                id: restoreButton
                width: graphSettingRect.width - pointColorLabel.width - 10
                height: 50//definedHeight
                textSize: width / 50 + 10
                showText: qsTr("Restore defaults")
                customText: showText
                onPressed: {
                    myparameters.reset()
                    pointColorButton.color = myparameters.pointColor
                    pointSlider.sliderValue = myparameters.pointSize
                    lineColorButton.color = myparameters.lineColor
                    lineSlider.sliderValue = myparameters.lineWidth
                    highlightColorButton.color = myparameters.highlightColor
                    highlightSlider.sliderValue = myparameters.highlightSize
                    axesColorButton.color = myparameters.axesColor
                    backgroundColorButton.color = myparameters.backgroundColor
                }
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
        flickable.contentY = 0
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
