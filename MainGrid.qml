import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5

import "qml/ButtonsRect"

Grid {
    id: grid
    anchors.centerIn: parent
    columns: 2
    spacing: 10

    property alias parametersButton: parametersButton
    property alias graphButton: graphButton
    property alias graphSettingsButton: graphSettingsButton
    property alias speechSettingsButton: speechSettingsButton
    
    CustomButton {
        id: parametersButton
        customText: qsTr("Function\nparameters")
        width: 200
        height: 100
        onPressed: parametersButtonPressed()
    }
    
    CustomButton {
        id: graphButton
        customText: qsTr("Show\ngraph")
        width: 200
        height: 100
        onPressed: graphButtonPressed()
    }
    
    CustomButton {
        id: graphSettingsButton
        customText: qsTr("Graph\nsettings")
        width: 200
        height: 100
        onPressed: graphSettingsPressed()
    }
    
    CustomButton {
        id: speechSettingsButton
        customText: qsTr("Speech settings")
        width: 200
        height: 100
        onPressed: speechSettingsButtonPressed()
    }
    
    CustomButton {
        id: rect2Button
        customText: qsTr("Show\nrect2")
        width: 200
        height: 100
        onPressed: rect2ButtonPressed()
    }
    
    CustomButton {
        id: tableButton
        customText: qsTr("Show\ntable")
        width: 200
        height: 100
    }

    Component.onCompleted: {
        parametersButton.forceActiveFocus()
        parametersButton.isPressed = true
        parametersButton.isActive = true
    }
}
