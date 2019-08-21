import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQml 2.2

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    property alias xStart: controlsContainer.xStart
    property alias xEnd: controlsContainer.xEnd
    property alias yStart: controlsContainer.yStart
    property alias yEnd: controlsContainer.yEnd
    property alias drawLinesEnabled: controlsContainer.drawLinesEnabled

    ControlsContainer {
        id: controlsContainer
    }

    MyCanvas {
        id: canvas
        anchors {
            top: parent.top
            bottom: parent.bottom
            right: parent.right
            left: controlsContainer.right
        }
    }

    MouseArea {
        id: mouseArea
        anchors {
            top: parent.top
            bottom: parent.bottom
            right: parent.right
            left: controlsContainer.right
        }
        onPressed: {
            canvas.mousePressed(mouseX, mouseY)
            androidClient.speak(mouseX)
        }
        onReleased: {
            androidClient.vibrate(mouseX)
        }
    }

    onXStartChanged: canvas.xStart = xStart
    onXEndChanged: canvas.xEnd = xEnd
    onYStartChanged: canvas.yStart = yStart
    onYEndChanged: canvas.yEnd = yEnd
    onDrawLinesEnabledChanged: canvas.drawLinesEnabled = drawLinesEnabled
}
