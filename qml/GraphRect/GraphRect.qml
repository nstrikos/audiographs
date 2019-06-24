import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.3

import CustomGeometry 1.0

import "../.."

Rectangle {
    id: graphRect

    //anchors.fill: parent
    focus: true
    visible: false
    color: "white"

    layer.enabled: true
    layer.samples: 256

    property int state: 1

    property var xLineCoords: []
    property var yLineCoords:[]
    property alias curve: curve

    onWidthChanged: controlsRect.calculate()
    onHeightChanged: controlsRect.calculate()

    MultiPointTouchArea {
        id: multiPointTouchArea
        anchors.fill: parent
        touchPoints: [
            TouchPoint {
                id: point1
                onXChanged: handleState3()
                onPressedChanged: handleState3()
            },
            TouchPoint { id: point2 },
            TouchPoint { id: point3 },
            TouchPoint { id: point4 }
        ]
        onPressed: handleMultiPointTouchArea()
    }



    PinchArea {
        anchors.fill: parent
        onPinchStarted: controlsRect.startPinch()
        onPinchUpdated: controlsRect.handlePinch(pinch.scale)

        MouseArea {
            anchors.fill: parent
            onWheel: controlsRect.handleZoom(wheel.angleDelta.y)
            scrollGestureEnabled: false

            property var x0
            property var y0
            property var mousePressed

            onPressedChanged: {
                if (pressed) {
                    mousePressed = true
                    x0 = mouseX
                    y0 = mouseY
                    controlsRect.startDrag()
                }
                else {
                    mousePressed = false
                }
            }

            onPositionChanged: {
                if (mousePressed)
                    controlsRect.handleDrag(mouseX - x0, mouseY - y0)
            }
        }
    }

    Curve {
        id: curve
        anchors.fill: parent
        layer.enabled: true
        layer.samples: 256
    }

    GraphCanvas {
        id: graphCanvas
        visible: false
        anchors.fill: parent
    }

    GraphCanvas {
        id: pointCanvas
        visible: true
        anchors.fill: parent
    }

    BeautifyGraphRect {

    }

    BeautifyGraphRect {
        anchors.top: parent.top
        anchors.bottom: undefined
        height: 8
        visible: (settingsRect.height > 0) && (!anchorToLeft)

        gradient: Gradient {
            GradientStop {
                color: Qt.rgba(0, 0, 0, 0.4)
                position: 0
            }
            GradientStop {
                color: Qt.rgba(0, 0, 0, 0.15)
                position: 0.5
            }
            GradientStop {
                color: Qt.rgba(0, 0, 0, 0)
                position: 1
            }
        }
    }

    BeautifyRect {
        visible: (settingsRect.width > 0)
    }



    function draw() {
        xLineCoords = myfunction.xLineCoords
        yLineCoords = myfunction.yLineCoords
        curve.draw(xLineCoords, yLineCoords)
    }

    function updatePoints() {
        graphCanvas.updatePoints();
        pointCanvas.updatePoints();
        visible = true
        graphCanvas.visible = true
    }

    function startPoints() {
        pointCanvas.startPoints()
    }

    function escapePressed() {
        stopAudio()
        graphRect.visible = false
        grid.visible = true
        grid.graphButton.forceActiveFocus()
    }

    function handleMultiPointTouchArea() {

        if (point4.pressed) {
            handle3Points()
        }
        else if (point3.pressed)
            handle2Points()
//        else if (point2.pressed)
//            handle2Points()
        else
            handle1Point()
    }

    function handle1Point() {
        if (state === 1) {
            test.stop();
            test.start(mainWindow.expression,
                       0,//parametersRect.minimumXText,
                       5,//parametersRect.maximumXText,
                       myparameters.duration,
                       200,//myparameters.minFreq,
                       2000);//myparameters.maxFreq);
            graphRect.startPoints()
        }
        else if (state === 2) {
            pointCanvas.drawCurrentPoint()
        }
        else if (state === 3) {
            //mouseArea.enabled = true
            //console.log(point1.x)
        }
    }

    function handle2Points() {
        if (state === 1)
            stopAudio()
        else if (state === 2)
            pointCanvas.drawCurrentPoint2()
    }

    function handle3Points() {
        stopAudio()
        state++

        if (state === 3)
//            console.log(point1.x)
//            mouseArea.accept = true
//        else
//            mouseArea.accept = false

        if (state > 3)
            state = 1
//        console.log("state: ", state)
    }

    function handleState3() {
        if (state === 3) {
            //console.log(point1.x)
            if (point1.pressed)
                pointCanvas.drawMousePoint(point1.x, graphRect.width)
            else
                stopAudio()
        }

    }

    function stopAudio() {
        test.stop();
        audioPoints.stopAudio()
        pointCanvas.stopPoints()
    }

    Keys.onEscapePressed: escapePressed()
    Keys.onBackPressed: escapePressed()

    Keys.onDigit1Pressed: handle1Point()
    Keys.onDigit2Pressed: handle2Points()
    Keys.onDigit3Pressed: handle3Points()
    Keys.onDigit4Pressed: state = 4
}
