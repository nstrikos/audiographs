import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5

import "qml/ButtonsRect"
import "qml/ParametersRect"
import "qml/GraphRect"
import "qml/GraphSetting"
import "qml/"

Window {
    id: window
    visible: true
    width: 640
    height: 550
    minimumWidth: 480
    minimumHeight: 640
    title: qsTr("Sound graphs")

    Item {
        anchors.fill: parent
        focus: true
        Keys.onEscapePressed: window.close()
        Keys.onBackPressed: window.close()

        Grid {
            id: grid
            anchors.centerIn: parent
            columns: 2
            spacing: 10

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
        }

        ParametersRect {
            id: parametersRect
        }

        GraphRect {
            id: graphRect
        }

        GraphSettingRect {
            id: graphSettingRect
        }

        SpeechSettings {
            id: speechSettings
            width: parent.width
            height: parent.height
        }

        Rectangle {
            id: rect2
            anchors.fill: parent
            visible: false

            property alias seconds: slider1.value
            property alias fmin: slider2.value
            property alias fmax: slider3.value

            CustomButton {
                id: button1
                onPressed: {
                    rect2.visible = false
                    grid.visible = true
                }
            }

            Slider {
                id: slider1
                anchors.top: button1.bottom
                from: 10
                to: 60
                stepSize: 1
            }
            Label {
                anchors.top: button1.bottom
                anchors.left: slider1.right
                text: slider1.value
                font.pointSize: 20
            }
            Slider {
                id: slider2
                anchors.top: slider1.bottom
                from: 200
                to: 6000
                stepSize: 100
            }
            Label {
                anchors.top: slider1.bottom
                anchors.left: slider2.right
                text: slider2.value
                font.pointSize: 20
            }
            Slider {
                id: slider3
                anchors.top: slider2.bottom
                from: 200
                to: 6000
                value: 6000
                stepSize: 100
            }
            Label {
                anchors.top: slider2.bottom
                anchors.left: slider3.right
                text: slider3.value
                font.pointSize: 20
            }
            Slider {
                id: slider
                anchors.top: slider3.bottom
                from: 1
                to: 3
                value: 1
                stepSize: 1
                width: parent.width
                onValueChanged: {
                    if (value === 1) {
                        graphRect.mouseArea.visible = true
                        graphRect.multiPointTouchArea.visible = false
                        androidClient.speak("Test")
                    }
                    if (value === 2) {
                        graphRect.mouseArea.visible = false
                        graphRect.multiPointTouchArea.visible = true
                        androidClient.vibrate("Test")
                    }
                }
            }

        }
    }

    function parametersButtonPressed() {
        grid.visible = false
        parametersRect.visible = true
        parametersRect.forceActiveFocus()
    }

    function graphButtonPressed() {
        //ButtonFunctions.clear()
        grid.visible = false
        graphRect.visible = true
        graphRect.forceActiveFocus()
        //graphButton.isPressed = true
        myfunction.calculate(parametersRect.functionText,
                             parametersRect.minimumXText,
                             parametersRect.maximumXText,
                             parametersRect.stepText)
    }

    function graphSettingsPressed() {
        grid.visible = false
        graphSettingRect.visible = true
        graphSettingRect.setFocus()
    }

    function rect2ButtonPressed() {
        grid.visible = false
        rect2.visible = true
    }

    function speechSettingsButtonPressed() {
        grid.visible = false
        speechSettings.visible = true
        speechSettings.setActiveFocus()
    }

    function tableButtonPressed() {
        ButtonFunctions.clear()
        tableButton.isPressed = true
        rect3.visible = true
        rect3.input5.forceActiveFocus()
    }

    Connections {
        target: myfunction
        onUpdate: {
            graphRect.updatePoints()
            test.stop();
            test.start(parametersRect.functionText,
                       parametersRect.minimumXText,
                       parametersRect.maximumXText,
                       rect2.seconds,
                       rect2.fmin,
                       rect2.fmax);
            graphRect.startPoints()
        }
        onError: console.log(err)
    }

    Component.onCompleted: {
        parametersButton.forceActiveFocus()
        parametersButton.isPressed = true
        parametersButton.isActive = true
    }
}
