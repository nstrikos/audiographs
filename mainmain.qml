import QtQuick 2.0
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12


import "qml/GraphRect"
import "qml/MainGrid"

Window {
    id: window
    visible: true
    width: 380
    height: 350
    minimumWidth: 320
    minimumHeight: 320
    title: qsTr("Audio graphs")

    property alias myItem: myItem

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
                }
                AnchorChanges {
                    target: graphRect
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    anchors.left: controlsRect.right
                    anchors.right: parent.right
                }
                AnchorChanges {
                    target: settingsRect
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                }

                AnchorChanges {
                    target: controlsButton
                    anchors.top: parent.top
                    anchors.left: graphRect.left
                }

                AnchorChanges {
                    target: settingsButton
                    anchors.top: parent.top
                    anchors.right: graphRect.right
                }

                PropertyChanges {
                    target: settingsRect
                    width: 0
                }
                PropertyChanges {
                    target: controlsRect
                    width: window.width / 3
                }
                PropertyChanges {
                    target: graphRect
                    width: window.width * 2/3
                }
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

                AnchorChanges {
                    target: graphRect
                    anchors.left: parent.left
                    //                    anchors.right: settingsRect.left
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                }

                PropertyChanges {
                    target: graphRect
                    width: window.width * 2 / 3
                }

                AnchorChanges {
                    target: settingsRect
                    anchors.left: graphRect.right
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
            }
        ]
    }

    property var expression
    property bool anchorToLeft: undefined

    onAnchorToLeftChanged: {
        clearAnchors()
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
    }

    ControlsButton {
        id: controlsButton
        z: 100
    }

    GraphRect {
        id: graphRect
        visible: true
        z: 10
    }

    SettingsRect {
        id: settingsRect
    }

    SettingsButton {
        id: settingsButton
        z: 100
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
            graphRect.draw()
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
