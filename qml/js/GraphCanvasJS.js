function paintCanvas()
{
    initializeCanvas()
    initializeArrays()
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
//        ctx.fillStyle = myparameters.backgroundColor;
        ctx.fillStyle = "rgba(255, 255, 255, 0)";
        ctx.fillRect(0, 0, canvas.width, canvas.height)
    }
}

function initializeArrays()
{
    xGridValues.length = 0
    yGridValues.length = 0
    xGridCoords.length = 0
    yGridCoords.length = 0
}

function draw()
{
    drawGrid()

    requestPaint()
}

function drawGrid()
{
    drawAxes()

    var xStart = myfunction.minX()
    var xEnd = myfunction.maxX()
    var xInterval = findInterval(xEnd - xStart)
    findVerticalGridLines(xStart, xEnd, xInterval)

    ctx.lineWidth = 0.1
    //ctx.setLineDash([1, 4]);
    ctx.strokeStyle = myparameters.axesColor;

    drawVerticalLines()

    var yStart = myfunction.minY()
    var yEnd = myfunction.maxY()
    var yInterval = findInterval(yEnd - yStart)
    findHorizontalGridLines(yStart, yEnd, yInterval)
    drawHorizontalLines()
    ctx.setLineDash([]);
    ctx.stroke()
}

function drawAxes()
{
    var x0 = myfunction.minX()
    var x1 = myfunction.maxX()
    var y0 = myfunction.minY()
    var y1 = myfunction.maxY()
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
    if (y1 > y0) {
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
