import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5

import "../js/ButtonFunctions.js" as ButtonFunctions

Rectangle {
    id: buttonsRect

    property alias parametersButton: parametersButton

    width: 200
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    anchors.left: parent.left
    color: "lightgray"

    Column {
        anchors.fill: parent
        spacing: 5

        CustomButton {
            id: parametersButton
            customText: qsTr("Function\nparameters")
            onPressed: parametersButtonPressed()
            KeyNavigation.tab: graphButton
            KeyNavigation.backtab: buttonPreviousTab()
        }
        
        CustomButton {
            id: graphButton
            customText: qsTr("Show\ngraph")
            onPressed: graphButtonPressed()
            KeyNavigation.tab: rect2Button
        }

        CustomButton {
            id: rect2Button
            customText: qsTr("Show\nrect2")
            onPressed: rect2ButtonPressed()
            KeyNavigation.tab: tableButton
        }

        CustomButton {
            id: tableButton
            customText: qsTr("Show\ntable")
            onPressed: tableButtonPressed()
            KeyNavigation.tab: buttonNextTab()
        }
    }

    function parametersButtonPressed() {
        ButtonFunctions.clear()
        parametersButton.isPressed = true
        parametersRect.visible = true
        parametersRect.forceActiveFocus()
    }

    function graphButtonPressed() {
        ButtonFunctions.clear()
        graphRect.visible = true
        graphButton.isPressed = true
        myfunction.calculate(parametersRect.functionText,
                             parametersRect.minimumXText,
                             parametersRect.maximumXText,
                             parametersRect.stepText)
    }

    function rect2ButtonPressed() {
        ButtonFunctions.clear()
        rect2Button.isPressed = true
        rect2.visible = true
        rect2.input3.forceActiveFocus()

    }

    function tableButtonPressed() {
        ButtonFunctions.clear()
        tableButton.isPressed = true
        rect3.visible = true
        rect3.input5.forceActiveFocus()
    }

    function buttonNextTab() {
        if (parametersRect.visible)
            return parametersRect.functionInput
        else if (rect2.visible)
            return rect2.input3
        else
            return rect3.input5
    }

    function buttonPreviousTab() {
        if (parametersRect.visible)
            return parametersRect.checkDrawLine
        else if (rect2.visible)
            return rect2.checkboxDrawLine
        else
            return rect3.input6
    }

    Component.onCompleted: {
        parametersButton.forceActiveFocus()
        parametersButton.isPressed = true
        parametersButton.isActive = true
    }
}
