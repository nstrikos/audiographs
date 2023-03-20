import "../BeautityRect"
import "./Focus"

import "../SettingsRect/AudioSettings"
//import "../SettingsRect/GraphSettings"

import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.3

FocusScope {
    id: selfVoiceFocusScope
    height: 30
    width: 150
    anchors.verticalCenter: audioLabel8.verticalCenter
    anchors.right: parent.right
    anchors.rightMargin: 10
    property alias selfVoiceCheckBox: selfVoiceCheckBox
    property alias color: selfVoiceCheckBox.color
    activeFocusOnTab: true

    property bool completed: false

    Accessible.name: qsTr("Self voice")

    Keys.onSpacePressed: selfVoiceCheckBox.checked = !selfVoiceCheckBox.checked
    Keys.onEnterPressed: selfVoiceCheckBox.checked = !selfVoiceCheckBox.checked
    Keys.onReturnPressed: selfVoiceCheckBox.checked = !selfVoiceCheckBox.checked

    Rectangle {
        id: selfVoiceCheckBox
        anchors.fill: parent
        color: bgColor
        property bool checked: parameters.selfVoice
        border.color: selfVoiceFocusScope.activeFocus ? lightColor : "light gray"
        border.width: selfVoiceFocusScope.activeFocus ? 2 : 1
        Text {
            text: selfVoiceCheckBox.checked ? qsTr("On") : qsTr("Off")
            anchors.centerIn: parent
            font.pointSize: 16
            color: fontColor
        }

        MouseArea {
            anchors.fill: parent
            onPressed: {
                selfVoiceCheckBox.checked = !selfVoiceCheckBox.checked
            }
        }
        onCheckedChanged: {
            //window.stopAudio()
            parameters.selfVoice = checked
            if (completed)
                textToSpeech.speak(selfVoiceFocusScope.Accessible.name + " " + parameters.selfVoice)
        }
    }

    Component.onCompleted: completed = true
}

