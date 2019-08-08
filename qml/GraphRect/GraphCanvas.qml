import QtQuick 2.9
import QtQml 2.2

import "../js/GraphCanvasJS.js" as CanvasJS
import "../js/GraphCanvasMouseJS.js" as MouseJS

//What needs to be done
//--> find where the function is not continuous
//--> precision
//--> javascript has infinity
//--> check if xEnd > xStart, yEnd > yStart
//--> sin(x)/x at x = 0 the func gives 3.28????
//--> autoadjust height finding min and max
//--> announce when graph is completed
//--> put func computation to different thread, does this solve the problem of resizing in large inputs?

Canvas {
    id: canvas

    renderStrategy: Canvas.Immediate

    property color canvasColor: "#ffffff"

    property var ctx //Handle to canvas
    property var canvasData //canvas data for displaying pixels
    property bool canvasDataAreValid: false //Check if canvas is ready for drawing

    property var xCoords: [] //Store x screen coordinates
    property var yCoords: []
    property var xLineCoords: []
    property var yLineCoords:[]  //Store y screen coordinates
    property var xGridValues: [] //Store actual x grid coordinates
    property var yGridValues: [] //Store actual y grid coordiantes
    property var xGridCoords: [] //Store x grid screen coordinates
    property var yGridCoords: []
    property var timeElapsed//Store y grid screen coordinates

    property int currentPoint: 0

    function updatePoints() {

//        if (myfunction.size() > 0) {
            //            currentPoint = 0
            //            var interval = 10000 / myfunction.size();
            //            console.log(interval)
            //            timer.interval = interval

            //            timer.start()
            CanvasJS.paintCanvas()
//        }
    }

    function mousePressed(x, y) {
        MouseJS.mousePressed(x, y)
    }

    //Neither Component.onCompleted works nor onAvailableChanged
    //Component.onCompleted ctx points to null
    //onAvailableChanged height is zero

    Timer {
        id: timer
        interval: 500
        running: false
        onTriggered: {
            timer.running = false
            //CanvasJS.paintCanvas()
            //            CanvasJS.updatePoints()
            //            timer.restart()
            updatePoints()
        }
    }

    Timer {
        id: timer2
        interval: 250
        running: false
        onTriggered: {
            timeElapsed += interval
            if (timeElapsed > myparameters.duration * 1000) {
                currentPoint = -1;
                CanvasJS.paintCanvas()
            }
            else {

                currentPoint = Math.round( timeElapsed / (myparameters.duration * 1000) * myfunction.size())
                CanvasJS.drawCurrentPixel()
                //            CanvasJS.initializeCanvas()
                //            CanvasJS.initializeArrays()
                //            CanvasJS.draw()
                //            CanvasJS.updatePoints()
                timer2.restart()
            }
        }
    }

    function startPoints() {
        CanvasJS.paintCanvas()
        currentPoint = 0;
        timeElapsed = 0.0;
        timer2.running = true
        //        timer2.restart()
    }

    function stopPoints() {
        timer2.running = false
        currentPoint = -1
        CanvasJS.paintCanvas()
    }

    //Works for android
    //    onAvailableChanged: CanvasJS.paintCanvas()

    //Works for linux

    function drawMousePixel(x, y) {
        CanvasJS.drawMousePixel(x, y)
    }

    function drawCurrentPoint() {
        currentPoint++
        if (currentPoint >= myfunction.size())
            currentPoint = myfunction.size() - 1
        CanvasJS.drawCurrentPixel()
        var fmin = 200
        var fmax = 4000;
        //var y = m_function->y(m_curPoint);
        //qDebug() << "y: " << y;
        var a =  (fmax-fmin)/(myfunction.maxY - myfunction.minY);
//            qDebug() << m_yMax << " " << m_yMin << " " << a;
        var b = fmax - a * myfunction.maxY;
        var l = myfunction.y(currentPoint)

        var f = a * l + b;
        var freq = f;
        //audioPoints.setFreq(freq)
        l = Math.round(l * 100) / 100
        texttospeech.speak(l)
    }

    function drawCurrentPoint2() {
        currentPoint--
        if (currentPoint < 0)
            currentPoint = 0
        CanvasJS.drawCurrentPixel()
        var fmin = 200
        var fmax = 4000;
        //var y = m_function->y(m_curPoint);
        //qDebug() << "y: " << y;
        var a =  (fmax-fmin)/(myfunction.maxY - myfunction.minY);
//            qDebug() << m_yMax << " " << m_yMin << " " << a;
        var b = fmax - a * myfunction.maxY;
        var l = myfunction.y(currentPoint)

        var f = a * l + b;
        var freq = f;
        //audioPoints.setFreq(freq)
        l = Math.round(l * 100) / 100
        texttospeech.speak(l)
    }

    function start() {
        currentPoint = 0
        timer4.start()
    }

    Timer {
        id: timer4
        running: false
        interval: 10
        onTriggered: {
            currentPoint += 1
            if (currentPoint >= 100) {
                currentPoint = 0
                audioPoints.stopAudio()
                return
            }
            if (currentPoint < 0)
                currentPoint = 0
//            CanvasJS.drawCurrentPixel()
            var fmin = settingsRect.minFreq
            var fmax = settingsRect.maxFreq
            var a =  (fmax-fmin)/(myfunction.maxY2 - myfunction.minY2);
            var b = fmax - a * myfunction.maxY2;
            var l = myfunction.y(currentPoint)
            var f = a * l + b;
            var freq = f;
            audioPoints.setFreq(freq)
            timer4.start()
        }
    }

    function drawMousePoint(x, width) {
        var k = x / width * myfunction.size()
        currentPoint = Math.round(k)
        if (currentPoint >= myfunction.size())
            currentPoint = myfunction.size() - 1
        if (currentPoint < 0)
            currentPoint = 0
        CanvasJS.drawCurrentPixel()
        var fmin = settingsRect.minFreq
        var fmax = settingsRect.maxFreq
        var a =  (fmax-fmin)/(myfunction.maxY2 - myfunction.minY2);
        var b = fmax - a * myfunction.maxY2;
        var l = myfunction.y(currentPoint)
        var f = a * l + b;
        var freq = f;
        audioPoints.setFreq(freq)
    }

    function clear() {
        CanvasJS.clear()
    }
}
