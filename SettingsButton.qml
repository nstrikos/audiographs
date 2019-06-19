import QtQuick 2.0
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12


import "qml/GraphRect"
import "qml/MainGrid"

Item {
    id: rect4
    height: 50
    width: 50
    
    SettingsIcon {
        width: 50
        height: 50
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 5
    }
    
    MouseArea {
        anchors.fill: parent
        onClicked: {
            if (settingsRect.shown == false) {
                controlsRect.shown = false
                controlsRect.width = 0
                settingsRect.shown = true
                settingsRect.width = window.width / 3
            }
            else {
                settingsRect.shown = false
                settingsRect.width = 0
            }
        }
    }
    x: (settingsRect.width > 0) ? settingsRect.x : settingsRect.x - width
    z: 1000
}
