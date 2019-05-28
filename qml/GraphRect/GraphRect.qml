import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.3

Rectangle {
    id: graphRect

    anchors.fill: parent
    focus: true
    visible: false
    color: "white"

    property int state: 1



    MultiPointTouchArea {
        id: multiPointTouchArea
        anchors.fill: parent
        touchPoints: [
            TouchPoint {
                id: point1
                onXChanged: {
                    if (pressed && state === 3)
                        console.log(x,y)
                }
            },
            TouchPoint { id: point2 },
            TouchPoint { id: point3 },
            TouchPoint { id: point4 }
        ]
        onPressed: handleMultiPointTouchArea()
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

        }
        else if (point3.pressed)
            handle3Points()
        else if (point2.pressed)
            handle2Points()
        else
            handle1Point()
    }

    function handle1Point() {
        if (state === 1) {
            test.stop();
            test.start(parametersRect.functionText,
                       parametersRect.minimumXText,
                       parametersRect.maximumXText,
                       myparameters.duration,
                       myparameters.minFreq,
                       myparameters.maxFreq);
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
            console.log(point1.x)
//            mouseArea.accept = true
//        else
//            mouseArea.accept = false

        if (state > 4)
            state = 1
        console.log("state: ", state)
    }

    function stopAudio() {
        test.stop();
        pointCanvas.stopPoints()
    }

    Keys.onEscapePressed: escapePressed()
    Keys.onBackPressed: escapePressed()

    Keys.onDigit1Pressed: handle1Point()
    Keys.onDigit2Pressed: handle2Points()
    Keys.onDigit3Pressed: handle3Points()
    Keys.onDigit4Pressed: state = 4
}
