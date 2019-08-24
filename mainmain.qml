import QtQuick 2.0
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12


import "qml/GraphRect"
import "qml/MainGrid"

Window {
    id: window
    visible: true
    width: 320
    height: 350
    minimumWidth: 320
    minimumHeight: 320
    title: qsTr("Audio graphs")

    property alias myItem: myItem
    property alias modeButton: modeButton

    property int mode: 0

    Item {
        id: myItem
        states: [
            State {
                name: "state1"
                AnchorChanges {
                    target: controlsRect
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                    anchors.right: parent.horizontalCenter
                }
                AnchorChanges {
                    target: graphRect
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    anchors.left: controlsRect.right//parent.horizontalCenter//controlsRect.right
                    anchors.right: parent.right
                }
                AnchorChanges {
                    target: settingsRect
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    anchors.left: parent.right
                    anchors.right: parent.right
                }

                AnchorChanges {
                    target: controlsButton
                    anchors.top: parent.top
                    anchors.right: parent.horizontalCenter
                }

                AnchorChanges {
                    target: settingsButton
                    anchors.top: parent.top
                    anchors.right: graphRect.right
                }

                PropertyChanges {
                    target: controlsRect
                    anchors.rightMargin: window.width / 4
                }

                PropertyChanges {
                    target: settingsRect
                    anchors.leftMargin: 0
                }

                //                PropertyChanges {
                //                    target: settingsRect
                //                    width: 0
                //                }
                //                PropertyChanges {
                //                    target: controlsRect
                //                    width: window.width / 3
                //                }
                //                PropertyChanges {
                //                    target: graphRect
                //                    width: window.width * 2/3
                //                }
            },
            State {
                name: "state2"

                AnchorChanges {
                    target: controlsRect
                    anchors.left: parent.left
                    anchors.right: parent.left
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                }

                AnchorChanges {
                    target: graphRect
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                }

                AnchorChanges {
                    target: settingsRect
                    anchors.left: parent.right
                    anchors.right: parent.right
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                }

                AnchorChanges {
                    target: controlsButton
                    anchors.left: graphRect.left
                    anchors.top: parent.top
                }

                AnchorChanges {
                    target: settingsButton
                    anchors.right: graphRect.right
                    anchors.top: parent.top
                }

                PropertyChanges {
                    target: controlsRect
                    anchors.rightMargin: 0
                }

                PropertyChanges {
                    target: settingsRect
                    anchors.leftMargin: 0
                }
            },
            State {
                name: "state3"

                AnchorChanges {
                    target: controlsRect
                    anchors.left: parent.left
                    anchors.right: parent.left
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                }

                //                PropertyChanges {
                //                    target: graphRect
                //                    width: window.width * 2 / 3
                //                }

                AnchorChanges {
                    target: settingsRect
                    anchors.left: parent.horizontalCenter//graphRect.right
                    anchors.right: parent.right
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                }

                AnchorChanges {
                    target: controlsButton
                    anchors.left: graphRect.left
                    anchors.top: parent.top
                }

                AnchorChanges {
                    target: settingsButton
                    //anchors.right: graphRect.right
                    anchors.left: parent.horizontalCenter
                    anchors.top: parent.top
                }

                PropertyChanges {
                    target: controlsRect
                    anchors.rightMargin: 0
                }

                AnchorChanges {
                    target: graphRect
                    anchors.left: parent.left
                    anchors.right: settingsRect.left
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    //                    anchors.right: parent.horizontalCenter
                }
            },
            State {
                name: "state4"

                AnchorChanges {
                    target: graphRect
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.bottom: parent.verticalCenter
                }

                AnchorChanges {
                    target: controlsRect
                    anchors.top: graphRect.bottom
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                    anchors.right: parent.right
                }

                AnchorChanges {
                    target: settingsRect
                    anchors.top: parent.top
                    anchors.bottom: graphRect.top
                    anchors.left: parent.left
                    anchors.right: parent.right
                }

                PropertyChanges {
                    target: settingsRect
                    height: 0
                }

                PropertyChanges {
                    target: controlsRect
                    anchors.rightMargin: 0
                }

                PropertyChanges {
                    target: controlsButton
                    anchors.rightMargin: 0
                }

                PropertyChanges {
                    target: settingsRect
                    anchors.leftMargin: 0
                }

                AnchorChanges {
                    target: controlsButton
                    anchors.bottom: graphRect.bottom
                    anchors.right: graphRect.right
                }

                AnchorChanges {
                    target: settingsButton
                    anchors.top: graphRect.top
                    anchors.right: graphRect.right
                }
            },
            State {
                name: "state5"

                AnchorChanges {
                    target: graphRect
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                }

                AnchorChanges {
                    target: controlsRect
                    anchors.top: graphRect.bottom
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                    anchors.right: parent.right
                }

                AnchorChanges {
                    target: settingsRect
                    anchors.top: parent.top
                    anchors.bottom: graphRect.top
                    anchors.left: parent.left
                    anchors.right: parent.right
                }

                PropertyChanges {
                    target: settingsRect
                    height: 0
                }

                PropertyChanges {
                    target: controlsRect
                    anchors.rightMargin: 0
                }

                PropertyChanges {
                    target: controlsButton
                    anchors.rightMargin: 0
                }

                PropertyChanges {
                    target: settingsRect
                    anchors.leftMargin: 0
                }

                AnchorChanges {
                    target: controlsButton
                    anchors.bottom: graphRect.bottom
                    anchors.right: graphRect.right
                }

                AnchorChanges {
                    target: settingsButton
                    anchors.top: graphRect.top
                    anchors.right: graphRect.right
                }
            },
            State {
                name: "state6"

                AnchorChanges {
                    target: settingsRect
                    anchors.top: parent.top
                    anchors.bottom: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.right: parent.right
                }

                AnchorChanges {
                    target: graphRect
                    anchors.top: settingsRect.bottom
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                }

                AnchorChanges {
                    target: controlsRect
                    anchors.top: graphRect.bottom
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                    anchors.right: parent.right
                }

                AnchorChanges {
                    target: controlsButton
                    anchors.bottom: graphRect.bottom
                    anchors.right: graphRect.right
                }

                AnchorChanges {
                    target: settingsButton
                    anchors.top: graphRect.top
                    anchors.right: graphRect.right
                }

                AnchorChanges {
                    target: modeButton
                    anchors.top: graphRect.top
                    anchors.right: settingsButton.left
                }

                AnchorChanges {
                    target: modeButton2
                    anchors.top: graphRect.top
                    anchors.right: modeButton.left
                }

                AnchorChanges {
                    target: modeButton3
                    anchors.top: graphRect.top
                    anchors.right: modeButton2.left
                }

                PropertyChanges {
                    target: controlsRect
                    anchors.rightMargin: 0
                }

                PropertyChanges {
                    target: controlsButton
                    anchors.rightMargin: 0
                }

                PropertyChanges {
                    target: settingsRect
                    anchors.leftMargin: 0
                }
            }
        ]

        //        transitions: Transition {
        //            // smoothly reanchor myRect and move into new position
        //            AnchorAnimation { duration: 250 }
        //        }
    }

    property var expression
    property bool anchorToLeft: undefined

    onAnchorToLeftChanged: {
        //        clearAnchors()
        if (anchorToLeft == false) {
            if (myItem.state == 'state1')
                myItem.state = 'state4'
            else if (myItem.state == 'state2')
                myItem.state = 'state5'
            else if (myItem.state == 'state3')
                myItem.state = 'state6'
        } else if (anchorToLeft == true) {
            if (myItem.state == 'state4')
                myItem.state = 'state1'
            else if (myItem.state == 'state5')
                myItem.state = 'state2'
            else if (myItem.state == 'state6')
                myItem.state = 'state3'
        }
    }

    ControlsRect {
        id: controlsRect
        anchors.rightMargin: window.width / 4
    }

    ControlsButton {
        id: controlsButton
        anchors.rightMargin: window.width / 4 - width
        z: 100
    }

    GraphRect {
        id: graphRect
        visible: true
        z: 10
    }

    SettingsRect {
        id: settingsRect
        anchors.leftMargin: window.width / 8
    }

    SettingsButton {
        id: settingsButton
        z: 100
        anchors.leftMargin: window.width / 8 - width
    }

    Rectangle {
        id: modeButton
        z: 100
        anchors.right: settingsButton.left
        anchors.leftMargin: window.width / 8 - width
        anchors.top: parent.top
        anchors.topMargin: 10
        width: 30
        height: 30
        color: "lightgray"

        Image {
            anchors.fill: parent
            source: "qrc:/qml/images/240px-Speaker_Icon.svg.png"
        }

        property bool running: false

        onRunningChanged: {
            if (modeButton.running) {
                modeButton.color = "light green"
                timer1.running = true
                if (settingsRect.useNotes == true) {
                    audioNotes.startNotes(myfunction,
                                          settingsRect.minFreq,
                                          settingsRect.maxFreq,
                                          settingsRect.duration)
                } else {
                    test.start(controlsRect.expression,
                               controlsRect.textInput2.text,
                               controlsRect.textInput3.text,
                               settingsRect.duration,
                               settingsRect.minFreq,
                               settingsRect.maxFreq)
                }
                graphRect.curveMovingPoint.drawPoint(myfunction, settingsRect.duration)
            } else {
                modeButton.color = "lightgray"
                graphRect.curveMovingPoint.stopPoint()
                timer1.running = false
                test.stop()
                audioNotes.stopNotes()
            }
        }

        MouseArea {
            anchors.fill: parent
            onPressed: {
                modeButton2.running = false
                modeButton3.running = false
                modeButton.running = !modeButton.running
            }
        }

        Timer {
            id: timer1
            running: false
            interval: settingsRect.duration * 1000
            onTriggered: {
                modeButton.running = false
                modeButton.color = "lightgray"
            }
        }
    }

    Rectangle {
        id: modeButton2
        z: 100
        anchors.right: modeButton.left
        anchors.leftMargin: window.width / 8 - width
        anchors.rightMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 10
        width: 30
        height: 30
        color: "lightgray"

        Image {
            anchors.fill: parent
            source: "qrc:/qml/images/240px-Speaker_Icon.svg.png"
        }

        property bool running: false

        onRunningChanged: {
            if (modeButton2.running) {
                modeButton2.color = "light green"
                window.mode = 1
            } else {
                modeButton2.color = "lightgray"
                window.mode = 0
            }
        }

        MouseArea {
            anchors.fill: parent
            onPressed: {
                modeButton2.running = !modeButton2.running
                modeButton.running = false
                modeButton3.running = false
                graphRect.start()
            }
        }
    }

    Rectangle {
        id: modeButton3
        z: 100
        anchors.right: modeButton2.left
        anchors.leftMargin: window.width / 8 - width
        anchors.rightMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 10
        width: 30
        height: 30
        color: "lightgray"

        Image {
            anchors.fill: parent
            source: "qrc:/qml/images/240px-Speaker_Icon.svg.png"
        }

        property bool running: false

        onRunningChanged: {
            if (modeButton3.running) {
                modeButton3.color = "light green"
                window.mode = 2
                graphRect.multipointTouchArea.enabled = true
                graphRect.pointCanvas.visible = false
                graphRect.curve.visible = false
                graphRect.graphCanvas.visible = false
            } else {
                modeButton3.color = "lightgray"
                window.mode = 0
                graphRect.multipointTouchArea.enabled = false
                graphRect.pointCanvas.visible = true
                graphRect.curve.visible = true
                graphRect.graphCanvas.visible = true
            }
        }

        MouseArea {
            anchors.fill: parent
            onPressed: {
                modeButton3.running = !modeButton3.running
                modeButton2.running = false
                modeButton.running = false
            }
        }
    }

    onWidthChanged: setAnchor()
    onHeightChanged: setAnchor()

    function setAnchor() {

        if (width >= height)
            anchorToLeft = true
        else
            anchorToLeft = false
    }

    function clearAnchors() {
        controlsRect.anchors.top = undefined
        controlsRect.anchors.bottom = undefined
        controlsRect.anchors.left = undefined
        controlsRect.anchors.right = undefined
        graphRect.anchors.top = undefined
        graphRect.anchors.bottom = undefined
        graphRect.anchors.left = undefined
        graphRect.anchors.right = undefined
        settingsRect.anchors.top = undefined
        settingsRect.anchors.bottom = undefined
        settingsRect.anchors.left = undefined
        settingsRect.anchors.right = undefined
        controlsButton.anchors.top = undefined
        controlsButton.anchors.bottom = undefined
        controlsButton.anchors.left = undefined
        controlsButton.anchors.right = undefined
        settingsButton.anchors.top = undefined
        settingsButton.anchors.bottom = undefined
        settingsButton.anchors.left = undefined
        settingsButton.anchors.right = undefined
    }

    Connections {
        target: myfunction
        onUpdate: {
            graphRect.updatePoints()
        }
        onError: console.log(err)
    }

    Component.onCompleted: {
        setAnchor()
        if (anchorToLeft)
            myItem.state = 'state1'
        else
            myItem.state = 'state4'
    }
}
