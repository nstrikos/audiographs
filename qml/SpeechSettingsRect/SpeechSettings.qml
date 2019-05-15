import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

import "../js/ButtonFunctions.js" as ButtonFunctions

Item {
    id: window
    visible: false
    width: 640
    height: 480

    focus: true

    Keys.onBackPressed: {
        backPressed()
    }

    Keys.onEscapePressed: {
        backPressed()
    }

    function backPressed() {
        visible = false
        grid.visible = true
        grid.speechSettingsButton.forceActiveFocus()
    }

    function setActiveFocus() {
        textEdit.forceActiveFocus()
    }

    ColumnLayout {
        spacing: 0
        anchors.fill: parent

        TextEdit {
            id: textEdit
            Layout.fillWidth: true
            font.pointSize: 50
            Layout.fillHeight: true
            readOnly: true
            text: "Audiographs\n1 2 3 4 5 6 7 8 9 10"
            wrapMode: TextEdit.Wrap
            activeFocusOnTab: true
        }


        Row {
            id: row1
            Layout.fillWidth: true
            Label {
                id: label1
                text: qsTr("Volume: ") + slider1.value
                width: 150
                font.pointSize: 20
                anchors.verticalCenter: row1.verticalCenter
            }
            Slider {
                id: slider1
                anchors.verticalCenter: row1.verticalCenter
                width: window.width - label1.width
                value: 50
                stepSize: 1
                from: 0
                to: 100
                onValueChanged: texttospeech.volume = value
            }
        }

        Row {
            id: row2
            Layout.fillWidth: true
            Label {
                id: label2
                text: qsTr("Rate: ") + slider2.value
                width: 150
                font.pointSize: 20
                anchors.verticalCenter: row2.verticalCenter
            }
            Slider {
                id: slider2
                anchors.verticalCenter: row2.verticalCenter
                width: window.width - label2.width
                value: 50
                stepSize: 1
                from: -100
                to: 100
                onValueChanged: texttospeech.rate = value
            }
        }

        Row {
            id: row3
            Layout.fillWidth: true
            Label {
                id: label3
                text: qsTr("Pitch: ") + slider3.value
                width: 150
                anchors.verticalCenter: row3.verticalCenter
                font.pointSize: 20
            }
            Slider {
                id: slider3
                anchors.verticalCenter: row3.verticalCenter
                width: window.width - label3.width
                value: 50
                stepSize: 1
                from: -100
                to: 100
                onValueChanged: {
                    texttospeech.pitch = value
                    //myparameters.pitch = value
                }
            }
        }

        Row {
            width: window.width
            Button {
                id: button
                property bool isActive: false
                property bool isPressed: false
                text: qsTr("Test speech")
                width: window.width
                height: 80
                font.pointSize: 25
                onPressed:  {
                    texttospeech.speak(textEdit.text)
                }

                background: Rectangle {
                    implicitHeight: 100
                    radius: 10
                    border.color: {
                        if (button.isActive)
                            return "red"
                        else
                            return "gray"
                    }
                    color: button.isActive ? "lightblue": "white"
                    border.width: 5
                }

                onFocusChanged:     if (activeFocus) {
                                        isActive = true
                                        androidClient.speak(button.text)
                                    }
                                    else {
                                        isActive = false
                                    }

            }
        }
    }

    Component.onCompleted: {
        slider1.value = Math.round(texttospeech.volume * 100)
        slider2.value = Math.round(texttospeech.rate * 100)
        slider3.value = Math.round(texttospeech.pitch * 100)
    }
}
