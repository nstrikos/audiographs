import QtQuick 2.12
import QtQuick.Controls 2.12

import "../BeautityRect"
import "./Focus"

import "../SettingsRect/AudioSettings"
//import "../SettingsRect/GraphSettings"

import QtQuick.Dialogs 1.3

Button {
    id: helpButton
    text: qsTr("Help")
    anchors.top: graphResetButton.bottom
    anchors.topMargin: 30
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.leftMargin: 10
    anchors.rightMargin: 10
    width: 80
    height: 50
    Accessible.name: qsTr("Help button")

    contentItem: Text {
        text: helpButton.text
        font: helpButton.font
        opacity: enabled ? 1.0 : 0.3
        color: fontColor
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }
    background: Rectangle {
        implicitWidth: 100
        implicitHeight: 40
        opacity: enabled ? 1 : 0.3
        color: bgColor
        radius: 2
        border.color: helpButton.activeFocus ? lightColor : "light gray"
        border.width: helpButton.activeFocus ? 2 : 1
    }

    onFocusChanged: {
        controlRectFlickable.ensureVisible(helpButton)
    }

    onClicked: {

    }
}
