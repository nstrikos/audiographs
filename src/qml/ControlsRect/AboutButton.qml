import QtQuick 2.12
import QtQuick.Controls 2.12

import "../BeautityRect"
import "./Focus"

import "../SettingsRect/AudioSettings"
//import "../SettingsRect/GraphSettings"

import QtQuick.Dialogs 1.3

Button {
    id: aboutButton
    text: qsTr("About")
    anchors.top: helpButton.bottom
    anchors.topMargin: 30
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.leftMargin: 10
    anchors.rightMargin: 10
    width: 80
    height: 50
    Accessible.name: qsTr("About button")

    contentItem: Text {
        text: aboutButton.text
        font: aboutButton.font
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
        border.color: aboutButton.activeFocus ? lightColor : "light gray"
        border.width: aboutButton.activeFocus ? 2 : 1
    }

    onFocusChanged: {
        controlRectFlickable.ensureVisible(aboutButton)
    }

    onClicked: {

    }
}
