import QtQuick 2.0
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12


import "qml/GraphRect"
import "qml/MainGrid"

Item {
    id: controlsButton
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
        onPressed: {

            if (anchorToLeft) {
                if (controlsRect.shown == false) {
                    settingsRect.shown = false
                    settingsRect.width = 0
                    controlsRect.shown = true
                    //controlsRect.textInput.enabled = true
                    controlsRect.widthAnimation.start()
                }
                else {
                    controlsRect.shown = false
                    controlsRect.reverseWidthAnimation.start()
                    //controlsRect.textInput.enabled = false
                }
            } else {
                if (controlsRect.shown == false) {
                    controlsRect.shown = true
                    controlsRect.height = window.height / 2
                    graphRect.reverseHeightAnimation.start()
                } else {
                    controlsRect.shown = false
                    controlsRect.height = 0
                    graphRect.heightAnimation.start()
                }
            }
        }
    }
    x: setX()//(controlsRect.width > 0) ?  graphRect.x - width : controlsRect.x
    y: setY()
    z: 1000

    function setX() {
        if (anchorToLeft) {
            if (controlsRect.width > 0)
                return graphRect.x - width
            else
                return controlsRect.x
        } else {
            return controlsRect.width - width
        }
    }

    function setY() {
        if (anchorToLeft) {
            return 0
        } else {
            return graphRect.height - height
        }
    }
}
