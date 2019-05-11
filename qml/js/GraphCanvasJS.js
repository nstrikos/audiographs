var previousPoint = 0
var oldPositionX = 0;
var oldPositionY = 0;

function paintCanvas()
{
    initializeCanvas()
    initializeArrays()
    calculateScreenCoords()
    draw()
}

function initializeCanvas()
{
    ctx = canvas.getContext("2d")

    if (canvas.width > 0 && canvas.height > 0) {
        //There is a problem initializing canvas, that's why we use canvasDataAreValid variable
        canvasDataAreValid = true
        canvasData = ctx.createImageData(canvas.width, canvas.height)
        ctx.reset()
        ctx.fillStyle = myparameters.backgroundColor;
        ctx.fillRect(0, 0, canvas.width, canvas.height)
    }
}

function initializeArrays()
{
    xGridValues.length = 0
    yGridValues.length = 0
    xGridCoords.length = 0
    yGridCoords.length = 0
    xCoords.length = 0
    yCoords.length = 0
    xLineCoords.length = 0
    yLineCoords.length = 0
}

function calculateScreenCoords()
{
    myfunction.calcScrCoords(canvas.width, canvas.height)
    xCoords = myfunction.xCoords
    yCoords = myfunction.yCoords
    xLineCoords = myfunction.xLineCoords
    yLineCoords = myfunction.yLineCoords
}

function draw()
{
    drawGrid()

    if (myparameters.showLine)
        drawLines()

    if (myparameters.showPoints)
        drawPixels()

    requestPaint()
}

function drawPixels()
{
    if (canvasDataAreValid) {
        for (var i = 0; i < xCoords.length; i++) {
            var centreX = xCoords[i];
            var centreY = yCoords[i];
            var radius = myparameters.pointSize;

            ctx.beginPath();
            ctx.fillStyle = myparameters.pointColor;
            ctx.moveTo(centreX, centreY);
            ctx.arc(centreX, centreY, radius, 0, 2 * Math.PI, false);
            ctx.lineTo(centreX, centreY);
            ctx.fill();
        }
    }
}

function drawLines()
{
    var x,y
    ctx.lineWidth = myparameters.lineWidth
    ctx.strokeStyle = myparameters.lineColor
    ctx.setLineDash([]);

    ctx.beginPath()

    //Go to first point without drawing a line
    y = yLineCoords[0]
    x = xLineCoords[0]
    ctx.moveTo(x, y)

    //Begin drawing lines
    for (var i = 1; i < xLineCoords.length; i++) {
        y = yLineCoords[i]
        x = xLineCoords[i]
        ctx.lineTo(x, y)
    }

    ctx.stroke()
}

function drawGrid()
{
    drawAxes()

    var xStart = myfunction.x(0)
    var xEnd = myfunction.x(myfunction.size() - 1)
    var xInterval = findInterval(xEnd - xStart)
    findVerticalGridLines(xStart, xEnd, xInterval)

    ctx.lineWidth = 0.1
    //ctx.setLineDash([1, 4]);
    ctx.strokeStyle = myparameters.axesColor;

    drawVerticalLines()

    var yStart = myfunction.minY
    var yEnd = myfunction.maxY
    var yInterval = findInterval(yEnd - yStart)
    findHorizontalGridLines(yStart, yEnd, yInterval)
    drawHorizontalLines()
    ctx.setLineDash([]);
    ctx.stroke()
}

function drawAxes()
{
    var x0 = myfunction.x(0)
    var x1 = myfunction.x(myfunction.size() - 1)
    var y0 = myfunction.minY
    var y1 = myfunction.maxY
    ctx.beginPath()
    ctx.lineWidth = 4
    ctx.strokeStyle = myparameters.axesColor;
    ctx.setLineDash([]);
    var xAxes =  Math.round( strip( canvas.width / (x1 - x0) * (0 - x0) ) )
    var yAxes = Math.round( strip(canvas.height / (y1 - y0) * (0 - y0) ) )
    ctx.moveTo(xAxes, 0)
    ctx.lineTo(xAxes, canvas.height)
    ctx.moveTo(0, canvas.height - yAxes)
    ctx.lineTo(canvas.width, canvas.height - yAxes)
    ctx.stroke()
}

function findInterval(diff)
{
    var m
    var times
    var interval
    var pow = Math.floor(Math.log10(diff)) - 1

    m = 10 * Math.pow(10, pow)
    times = diff / m
    if (times <= 10)
        interval = m

    m = 5 * Math.pow(10, pow)
    times = diff / m
    if (times <= 10)
        interval = m

    m = 4 * Math.pow(10, pow)
    times = diff / m
    if (times <= 10)
        interval = m

    m = 2 * Math.pow(10, pow)
    times = diff / m
    if (times <= 10)
        interval = m

    m = 1 * Math.pow(10, pow)
    times = diff / m
    if (times <= 10)
        interval = m

    return interval
}

function findVerticalGridLines(x0, x1, dl)
{
    var point = (x0)
    point = point / dl
    point = Math.floor(point)
    point = point * dl
    //tempGrid.push(Math.round( strip( canvas.width / (xEnd - xStart) * (point - xStart) ) ))
    //xGrid.push(point)

    var done = false
    while (!done) {
        point += dl
        var screenPoint = Math.round( strip( canvas.width / (x1 - x0) * (point - x0) ) )
        xGridCoords.push(screenPoint)
        var value = Math.round (point / dl) * dl
        xGridValues.push(value)

        if (point > x1)
            done = true
    }
}

function drawVerticalLines()
{
    ctx.beginPath()
    var i = 0;
    var x = 0;
    while ( i < xGridCoords.length) {
        x = xGridCoords[i];
        ctx.font = "10px sans-serif";
        ctx.fillStyle = myparameters.axesColor;
        var text = +parseFloat(xGridValues[i]).toFixed(5)
        var w = ctx.measureText(text).width
        if ( (x + w/2) >= canvas.width )
        {
            var pos = x - w/2 - 10
        }
        else if (x - w/2 <= 0) {
            console.log("Error: " + i)
            pos = 0
        }
        else
            pos = x - w/2
        ctx.fillText(text, pos, 10);
        ctx.moveTo(x, 0)
        ctx.lineTo(x, canvas.height)
        i++
    }
}

function findHorizontalGridLines(y0, y1, dl)
{
    var point = (y0)
    point = point / dl
    point = Math.floor(point)
    point = point * dl
    yGridCoords.push(canvas.height - Math.round( strip(canvas.height / (y1 - y0) * (point - y0) ) ))
    var value = Math.round (point / dl) * dl
    yGridValues.push(value)

    var done = false
    while (!done) {
        point += dl
        var screenPoint = Math.round( strip(canvas.height / (y1 - y0) * (point - y0) ) )
        screenPoint = canvas.height - screenPoint
        yGridCoords.push(screenPoint)
        value = Math.round (point / dl) * dl
        yGridValues.push(value)

        if (point > y1)
            done = true
    }
}

function drawHorizontalLines()
{
    var i = 0;
    var y = 0;
    while ( i < yGridCoords.length) {
        y = yGridCoords[i];
        ctx.fillStyle = myparameters.axesColor;
        if (i === (yGridCoords.length - 1) )
            ctx.fillText(+parseFloat(yGridValues[i]).toFixed(5), 0, y + 10);
        else
            ctx.fillText(+parseFloat(yGridValues[i]).toFixed(5), 0, y);
        ctx.moveTo(0, y)
        ctx.lineTo(canvas.width, y)
        i++
    }
}

function strip(number) {
    return (parseFloat(number).toPrecision(10));
}

function drawCurrentPixel()
{
    xCoords = myfunction.xCoords
    yCoords = myfunction.yCoords

    ctx = canvas.getContext("2d")
    var radius = myparameters.highlightSize;

    //    if (canvas.width > 0 && canvas.height > 0) {
    //There is a problem initializing canvas, that's why we use canvasDataAreValid variable
    //        canvasDataAreValid = true
    //        canvasData = ctx.createImageData(canvas.width, canvas.height)
    //        ctx.reset()
    ctx.clearRect(xCoords[previousPoint] - radius,
                  yCoords[previousPoint] - radius,
                  radius * 2,
                  radius * 2)
    //    }


    //    if (canvasDataAreValid) {
    //        if (currentPoint < myfunction.size()) {
    var centreX = xCoords[currentPoint];
    var centreY = yCoords[currentPoint];

    ctx.beginPath();
    ctx.fillStyle = myparameters.highlightColor;
    ctx.moveTo(centreX, centreY);
    ctx.arc(centreX, centreY, radius, 0, 2 * Math.PI, false);
    ctx.lineTo(centreX, centreY);
    ctx.fill();
    requestPaint()
    //        }
    //    }
    previousPoint = currentPoint
}

function drawMousePixel (x, y) {
    ctx = canvas.getContext("2d")

    if (canvas.width > 0 && canvas.height > 0) {
        //There is a problem initializing canvas, that's why we use canvasDataAreValid variable
        //        canvasDataAreValid = true
        //        canvasData = ctx.createImageData(canvas.width, canvas.height)
        //        ctx.reset()
        //        ctx.fillStyle = myparameters.backgroundColor;
        //        ctx.fillRect(0, 0, canvas.width, canvas.height)


        var radius = myparameters.highlightSize;

        ctx.clearRect(oldPositionX - radius,
                      oldPositionY - radius,
                      radius * 2,
                      radius * 2)
        oldPositionX = x;
        oldPositionY = y;
        var centreX = x;
        var centreY = y;

        ctx.beginPath();
        ctx.fillStyle = myparameters.highlightColor;
        ctx.moveTo(centreX, centreY);
        ctx.arc(centreX, centreY, radius, 0, 2 * Math.PI, false);
        ctx.lineTo(centreX, centreY);
        ctx.fill();
        requestPaint()

    }
}

function clear() {
    //ctx = canvas.getContext("2d")

    var radius = myparameters.highlightSize;

    if (canvas.width > 0 && canvas.height > 0) {
        ctx.clearRect(oldPositionX - radius,
                      oldPositionY - radius,
                      radius * 2,
                      radius * 2)
    }
    requestPaint()
}
