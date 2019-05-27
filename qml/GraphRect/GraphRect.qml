import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.3

Rectangle {
    id: graphRect

    anchors.fill: parent
    focus: true
    visible: false
    color: "white"

    MultiPointTouchArea {
        id: multiPointTouchArea
        anchors.fill: parent
        touchPoints: [
            TouchPoint { id: point1 },
            TouchPoint { id: point2 }
        ]
        onPressed: {
            if (point2.pressed) {
                //pointCanvas.drawCurrentPoint2()
                test.stop();
                pointCanvas.stopPoints()
            }
            else {
                //pointCanvas.drawCurrentPoint()
                test.stop();
                test.start(parametersRect.functionText,
                           parametersRect.minimumXText,
                           parametersRect.maximumXText,
                           myparameters.duration,
                           myparameters.minFreq,
                           myparameters.maxFreq);
                graphRect.startPoints()

            }
        }
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
        test.stop()
        pointCanvas.stopPoints()
        graphRect.visible = false
        grid.visible = true
        grid.graphButton.forceActiveFocus()
    }

    Keys.onEscapePressed: escapePressed()
    Keys.onBackPressed: escapePressed()
}
