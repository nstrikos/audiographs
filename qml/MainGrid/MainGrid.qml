import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5

Grid {
    id: grid
    anchors.centerIn: parent
    columns: 2
    spacing: 10

    property alias parametersButton: parametersButton
    property alias graphButton: graphButton
    property alias audioSettingsButton: audioSettingsButton
    property alias graphSettingsButton: graphSettingsButton
    property alias speechSettingsButton: speechSettingsButton
    property alias settingsOtherButton: settingsOtherButton

    property int buttonWidth: parent.width / 2 - 30
    
    CustomButton {
        id: parametersButton
        customText: qsTr("Function\nparameters")
        width: buttonWidth
        height: 100
        onPressed: parametersButtonPressed()
    }
    
    CustomButton {
        id: graphButton
        customText: qsTr("Show\ngraph")
        width: buttonWidth
        height: 100
        onPressed: graphButtonPressed()
    }

    CustomButton {
        id: audioSettingsButton
        customText: qsTr("Audio\nsettings")
        width: buttonWidth
        height: 100
        onPressed: audioSettingsButtonPressed()
    }
    
    CustomButton {
        id: graphSettingsButton
        customText: qsTr("Graph\nsettings")
        width: buttonWidth
        height: 100
        onPressed: graphSettingsPressed()
    }
    
    CustomButton {
        id: speechSettingsButton
        customText: qsTr("Speech settings")
        width: buttonWidth
        height: 100
        onPressed: speechSettingsButtonPressed()
    }    

    CustomButton {
        id: settingsOtherButton
        customText: qsTr("Other settings")
        width: buttonWidth
        height: 100
        onPressed: settingsOtherButtonPressed()
    }

    function parametersButtonPressed() {
        grid.visible = false
        parametersRect.visible = true
        parametersRect.forceActiveFocus()
    }

    function graphButtonPressed() {
        grid.visible = false        
//        console.log(parametersRect.stepText)
        myfunction.calculate(parametersRect.functionText,
                             parametersRect.minimumXText,
                             parametersRect.maximumXText,
                             parametersRect.stepText)
        graphRect.visible = true
        graphRect.forceActiveFocus()
    }

    function audioSettingsButtonPressed() {
        grid.visible = false
        audioSettingsRect.visible = true
        audioSettingsRect.setActiveFocus()
    }

    function graphSettingsPressed() {
        grid.visible = false
        graphSettingRect.visible = true
        graphSettingRect.setFocus()
    }

    function speechSettingsButtonPressed() {
        grid.visible = false
        speechSettings.visible = true
        speechSettings.setActiveFocus()
    }

    function settingsOtherButtonPressed() {
        grid.visible = false
        settingsOtherRect.visible = true
        settingsOtherRect.setActiveFocus()
    }

    Component.onCompleted: {
        parametersButton.forceActiveFocus()
        parametersButton.isPressed = true
        parametersButton.isActive = true
    }
}
