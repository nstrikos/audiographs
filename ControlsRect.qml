import QtQuick 2.0
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Styles.Flat 1.0 as Flat
import QtQuick.Layouts 1.12


import "qml/GraphRect"
import "qml/MainGrid"

Rectangle {
    id: rect
    //    height: 0//parent.height
    //    width: 0
    property bool shown: false
    property alias textInput: textInput
    property alias textInput2: textInput2
    property alias textInput3: textInput3

    property var expression
    property var minX
    property var maxX
    property var minY
    property var maxY
    property var points

    Rectangle {
        id: controlsTitleBar
        width: parent.width
        height: 54 * Flat.FlatStyle.scaleFactor
        color: Flat.FlatStyle.defaultTextColor
        z: 10000
        
        Label {
            text: (parent.width > 0) ? "Function parameters" : ""
            font.family: Flat.FlatStyle.fontFamily
            font.pixelSize: Math.round(12 * Flat.FlatStyle.scaleFactor)
            renderType: Text.QtRendering
            color: "white"
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

    Flickable {
        id: flickable
        width: parent.width
        anchors.top: controlsTitleBar.bottom
        anchors.topMargin: 40
        anchors.bottom: parent.bottom
        contentHeight: 500

        Item {
            id: controlsMainRect
            //            anchors.top: controlsTitleBar.bottom
            //            anchors.topMargin: 40
            width: parent.width

            Label {
                id: label1
                text: (parent.width > 0) ? "f(x) = " : ""
                anchors.left: parent.left
                anchors.leftMargin: 5
                width: 50
            }

            TextField {
                id: textInput
                anchors.left: label1.right
                anchors.leftMargin: 10
                anchors.right: parent.right
                anchors.rightMargin: 10
                anchors.verticalCenter: label1.verticalCenter
                placeholderText: (parent.width > 0) ? "Function expression" : ""
                height: 50
                selectByMouse: true
                onTextChanged: {
                    expression = text
                    textInput2.text = "-10"
                    textInput3.text = "10"
                    textInput4.text = "-5"
                    textInput5.text = "5"
                    textInput6.text = "1"
                    calculate()
                }
            }

            Label {
                id: label2
                text: (parent.width > 0) ? "min X : " : ""
                anchors.left: parent.left
                anchors.leftMargin: 5
                anchors.top: textInput.bottom
                anchors.topMargin: 40
                width: 50
            }

            TextField {
                id: textInput2
                anchors.left: label2.right
                anchors.leftMargin: 10
                anchors.verticalCenter: label2.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 10
                placeholderText: (parent.width > 0) ? "minimum X" : ""
                height: 50
                selectByMouse: true
                property bool active: true
                onTextChanged: {
                    if (active)
                        calculate()
                }
            }

            Label {
                id: label3
                text: (parent.width > 0) ? "max X : " : ""
                anchors.left: parent.left
                anchors.leftMargin: 5
                anchors.top: textInput2.bottom
                anchors.topMargin: 40
                width: 50
            }

            TextField {
                id: textInput3
                anchors.left: label3.right
                anchors.leftMargin: 10
                anchors.verticalCenter: label3.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 10
                placeholderText: (parent.width > 0) ? "maximum X" : ""
                height: 50
                selectByMouse: true
                property bool active: true
                onTextChanged: {
//                    maxX = text
                    if (active)
                        calculate()
                }
            }

            Label {
                id: label4
                text: (parent.width > 0) ? "min Y : " : ""
                anchors.left: parent.left
                anchors.leftMargin: 5
                anchors.top: textInput3.bottom
                anchors.topMargin: 40
                width: 50
            }

            TextField {
                id: textInput4
                anchors.left: label4.right
                anchors.leftMargin: 10
                anchors.verticalCenter: label4.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 10
                placeholderText: (parent.width > 0) ? "minimum Y" : ""
                height: 50
                selectByMouse: true
                property bool active: true
                onTextChanged: {
                    if (active)
                        calculate()
                }
            }

            Label {
                id: label5
                text: (parent.width > 0) ? "max Y : " : ""
                anchors.left: parent.left
                anchors.leftMargin: 5
                anchors.top: textInput4.bottom
                anchors.topMargin: 40
                width: 50
            }

            TextField {
                id: textInput5
                anchors.left: label5.right
                anchors.leftMargin: 10
                anchors.verticalCenter: label5.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 10
                placeholderText: (parent.width > 0) ? "maximum Y" : ""
                height: 50
                selectByMouse: true
                property bool active: true
                onTextChanged: {
                    if (active)
                        calculate()
                }
            }

            Label {
                id: label6
                text: (parent.width > 0) ? "Points : " : ""
                anchors.left: parent.left
                anchors.leftMargin: 5
                anchors.top: textInput5.bottom
                anchors.topMargin: 40
                width: 50
            }

            TextField {
                id: textInput6
                anchors.left: label4.right
                anchors.leftMargin: 10
                anchors.verticalCenter: label6.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 10
                placeholderText: (parent.width > 0) ? "number of points" : ""
                height: 50
                selectByMouse: true
                onTextChanged: calculate()
            }
        }
    }
    
    BeautifyRect {
    }
    
    function handleZoom(zoom) {
        var minX = Number(textInput2.text)
        var maxX = Number(textInput3.text)
        var minY = Number(textInput4.text)
        var maxY = Number(textInput5.text)

        if (zoom < 0) {
            minX = Math.round(minX * 1.10 * 100) / 100
            maxX = Math.round(maxX * 1.10 * 100) / 100
            minY = Math.round(minY * 1.10 * 100) / 100
            maxY = Math.round(maxY * 1.10 * 100) / 100
        } else {
            minX = Math.round(minX * 0.90 * 100) / 100
            maxX = Math.round(maxX * 0.90 * 100) / 100
            minY = Math.round(minY * 0.90 * 100) / 100
            maxY = Math.round(maxY * 0.90 * 100) / 100
        }

        textInput2.active = false
        textInput3.active = false
        textInput4.active = false
        textInput5.active = false


        textInput2.text = minX
        textInput3.text = maxX
        textInput4.text = minY
        textInput5.text = maxY
        calculate()

        textInput2.active = true
        textInput3.active = true
        textInput4.active = true
        textInput5.active = true

    }

    function startDrag() {
        minX = Number(textInput2.text)
        maxX = Number(textInput3.text)
        minY = Number(textInput4.text)
        maxY = Number(textInput5.text)
    }

    function handleDrag(diffX, diffY) {

        textInput2.active = false
        textInput3.active = false
        textInput4.active = false
        textInput5.active = false

        diffX = (maxX - minX) / graphRect.width * diffX
        diffY = (maxY- minY) / graphRect.height * diffY

        textInput2.text = Math.round( (minX - diffX) * 100) / 100
        textInput3.text = Math.round( (maxX - diffX) * 100) / 100
        textInput4.text = Math.round( (minY + diffY) * 100) / 100
        textInput5.text = Math.round( (maxY + diffY) * 100) / 100
        calculate()

        textInput2.active = true
        textInput3.active = true
        textInput4.active = true
        textInput5.active = true
    }

    function startPinch() {
        minX = Number(textInput2.text)
        maxX = Number(textInput3.text)
        minY = Number(textInput4.text)
        maxY = Number(textInput5.text)
    }

    function handlePinch(scale) {
        scale = 1 / scale
        textInput2.active = false
        textInput3.active = false
        textInput4.active = false
        textInput5.active = false

        textInput2.text = Math.round( scale * minX * 100) / 100
        textInput3.text = Math.round( scale * maxX * 100) / 100
        textInput4.text = Math.round( scale * minY * 100) / 100
        textInput5.text = Math.round( scale * maxY * 100) / 100
        calculate()

        textInput2.active = true
        textInput3.active = true
        textInput4.active = true
        textInput5.active = true
    }

    function calculate () {
        window.modeButton.running = false
        graphRect.curveMovingPoint.stopPoint()
        expression = textInput.text
        myfunction.calculate(textInput.text,
                             textInput2.text,
                             textInput3.text,
                             textInput4.text,
                             textInput5.text,
                             textInput6.text,
                             graphRect.width,
                             graphRect.height)
    }
}
