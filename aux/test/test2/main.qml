import QtQuick 2.9
import QtQuick.Controls 1.4
import QtQml 2.2

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Audiographs")

    signal graphSignal()

    property alias inputFunction: controlsContainer.inputFunction
    property alias xStart: controlsContainer.xStart
    property alias xEnd: controlsContainer.xEnd
    property alias yStart: controlsContainer.yStart
    property alias yEnd: controlsContainer.yEnd
    property alias h: controlsContainer.h
    property alias drawLinesEnabled: controlsContainer.drawLinesEnabled

    property bool firstRunning: false

    Rectangle {
        id: buttonsSelection
        color: Qt.lighter("grey")
        width: 200
        anchors {
            top: parent.top
            bottom: parent.bottom
            left: parent.left
        }

        Column {
            width: parent.width
            spacing: 5

            Button {
                id: parametersButton
                width: parent.width
                height: 50
                onClicked: {
                    canvas.visible = false
                    controlsContainer.visible = true
                    tableView.visible = false
                    controlsContainer.firstInputText.forceActiveFocus()
                    tableButton.nextTab = 0
                    console.log("ok")
                }
                text: "Parameters"
            }

            Button {
                width: parent.width
                height: 50
                onClicked: {
                    if (!firstRunning) {
                        firstRunning = true
                        graphSignal()
                    }
                    canvas.visible = true
                    canvas.forceActiveFocus()
                    controlsContainer.visible = false
                    tableView.visible = false
                    tableButton.nextTab = 1
                }
                text: "Show graph"
            }

            Button {
                id: tableButton
                property int nextTab: 0
                width: parent.width
                height: 50
                onClicked: {
                    canvas.visible = false
                    controlsContainer.visible = false
                    tableView.visible = true
                    tableView.forceActiveFocus()
                    nextTab = 2
                }
                text: "Table"
                Accessible.onPressAction: {
                    tableButton.clicked()
                }
                KeyNavigation.tab: controlsContainer.firstInputText
                onNextTabChanged: {
                    console.log(nextTab)
                    if (nextTab == 0)
                        KeyNavigation.tab = controlsContainer.firstInputText
                    else if (nextTab == 1)
                        KeyNavigation.tab = focusScope
                    else if (nextTab == 2) {
                        KeyNavigation.tab = tableView
                    }
                }

            }
        }
    }

    ControlsContainer {
        id: controlsContainer
        anchors {
            top: parent.top
            bottom: parent.bottom
            left: buttonsSelection.right
            right: parent.right
        }

        onGraphButtonPressed: {
            parser.functionString = inputFunction
            parser.xStart = xStart
            parser.xEnd = xEnd
            parser.yStart = yStart
            parser.yEnd = yEnd
            parser.h = h
            graphSignal()
            controlsContainer.visible = false
            canvas.visible = true
        }
    }

    FocusScope {
        id: focusScope
        anchors {
            top: parent.top
            bottom: parent.bottom
            right: parent.right
            left: buttonsSelection.right
        }
        KeyNavigation.tab: parametersButton

        MyCanvas {
            id: canvas
            visible: false
            anchors.fill: parent
            MouseArea {
                id: mouseArea
                anchors.fill: parent

                onPressed: {
                    canvas.mousePressed(mouseX, mouseY)
                    androidClient.speak(mouseX)
                    androidClient.vibrate(mouseX)
                    controlsContainer.visible = true
                    canvas.visible = false
                }
                onReleased: {
                    androidClient.vibrate(mouseX)
                }
            }
        }
    }

    TableView {
        id: tableView
    }

    function updatePoints() {
        canvas.updatePoints()
        focusScope.forceActiveFocus()
    }

    onDrawLinesEnabledChanged: canvas.drawLinesEnabled = drawLinesEnabled
}
