import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.3

Rectangle {
    id: graphRect

    property alias graphCanvas: graphCanvas
    property alias mouseArea : mouseArea
    property alias multiPointTouchArea: multiPointTouchArea

    anchors.fill: parent
    focus: true
    visible: false
    color: "white"
    MouseArea {id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onPressed: {
            //            graphCanvas.mousePressed(mouseX, mouseY)
            //androidClient.speak(mouseX)
            //androidClient.vibrate(mouseX)
            //controlsContainer.visible = true
            //canvas.visible = false


            //            pointCanvas.canvasDataAreValid = true
            //            pointCanvas.startPoints()

        }

        onMouseXChanged: {
            if (containsPress)
                drawMousePixel(mouseX)
        }

        onReleased: {
            //androidClient.vibrate(mouseX)
            //audioPoints.stopAudio()
            clear()
        }
    }

    MultiPointTouchArea {
        id: multiPointTouchArea
        anchors.fill: parent
        touchPoints: [
                    TouchPoint { id: point1 },
                    TouchPoint { id: point2 }
                ]
        onPressed: {
            if (point2.pressed)
                pointCanvas.drawCurrentPoint2()
            else
                pointCanvas.drawCurrentPoint()
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
        visible = true
        graphCanvas.visible = true
        graphCanvas.updatePoints();
    }

    function startPoints() {
        pointCanvas.startPoints()
    }

    function drawMousePixel(x) {
        var i = Math.round( x / graphCanvas.width * myfunction.size())
        if (i < myfunction.size()) {
            var j = myfunction.x(i)

            var x1 = myfunction.x(myfunction.size() - 1)
            var x0 = myfunction.x(0)
            var k = graphCanvas.width / (x1 - x0) * (j - x0)
            var l = myfunction.y(i)
            var y1 = myfunction.maxY
            var y0 = myfunction.minY
            var m = graphCanvas.height / (y1 - y0) * (l - y0)
            m = graphCanvas.height - m

            pointCanvas.drawMousePixel(k, m)

            var fmin = 200
            var fmax = 4000;
            //var y = m_function->y(m_curPoint);
            //qDebug() << "y: " << y;
            var a =  (fmax-fmin)/(myfunction.maxY - myfunction.minY);
//            qDebug() << m_yMax << " " << m_yMin << " " << a;
            var b = fmax - a * myfunction.maxY;
            var f = a * l + b;
            var freq = f;
            audioPoints.setFreq(freq)
        }
    }

    function clear() {
        pointCanvas.clear()
    }

    function escapePressed() {
        graphRect.visible = false
        grid.visible = true
        grid.graphButton.forceActiveFocus()
    }

    Keys.onEscapePressed: escapePressed()
    Keys.onBackPressed: escapePressed()
}
