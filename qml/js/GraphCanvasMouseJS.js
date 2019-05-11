function mousePressed(x, y)
{
    console.log("Pressed at x:" + x + ", y:" + y)
    var ctx = canvas.getContext("2d")
    ctx.fillStyle = "#33a9ff"
    ctx.beginPath()
    ctx.arc(x, y, 5, 0, 2*Math.PI)
    ctx.closePath()
    ctx.fill()
    canvas.requestPaint();
}
