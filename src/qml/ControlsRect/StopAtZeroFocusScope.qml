import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.3

FocusScope {
    id: stopAtZeroFocusScope
    height: 30
    width: 150
    anchors.verticalCenter: audioLabel9.verticalCenter
    anchors.right: parent.right
    anchors.rightMargin: 10
    property alias stopAtZeroCheckBox: stopAtZeroCheckBox
    property alias color: stopAtZeroCheckBox.color
    activeFocusOnTab: true

    property bool completed: false

    Accessible.name: qsTr("Stop sound at zero")

    Keys.onSpacePressed: stopAtZeroCheckBox.checked = !stopAtZeroCheckBox.checked
    Keys.onEnterPressed: stopAtZeroCheckBox.checked = !stopAtZeroCheckBox.checked
    Keys.onReturnPressed: stopAtZeroCheckBox.checked = !stopAtZeroCheckBox.checked

    Rectangle {
        id: stopAtZeroCheckBox
        anchors.fill: parent
        color: bgColor
        property bool checked: parameters.stopAtZero
        border.color: stopAtZeroFocusScope.activeFocus ? lightColor : "light gray"
        border.width: stopAtZeroFocusScope.activeFocus ? 2 : 1
        Text {
            text: stopAtZeroCheckBox.checked ? qsTr("On") : qsTr("Off")
            anchors.centerIn: parent
            font.pointSize: 16
            color: fontColor
        }

        MouseArea {
            anchors.fill: parent
            onPressed: {
                stopAtZeroCheckBox.checked = !stopAtZeroCheckBox.checked
            }
        }
        onCheckedChanged: {
            //window.stopAudio()
            parameters.stopAtZero = checked
            qmlConnector.stopAtZeroChanged()
            if (completed)
                textToSpeech.speak(stopAtZeroFocusScope.Accessible.name + " " + parameters.stopAtZero)
        }
    }

    Component.onCompleted: completed = true
}
