import QtQuick 2.0
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Styles.Flat 1.0 as Flat
import QtQuick.Layouts 1.12


import "qml/GraphRect"
import "qml/MainGrid"

Rectangle {
    id: settingsRect
    //    height: parent.height
    //    anchors.right: parent.right
    //    width: 0
    property bool shown: false
    z: -100

    Rectangle {
        id: settingsTitleBar
        width: parent.width
        height: 54 * Flat.FlatStyle.scaleFactor
        color: Flat.FlatStyle.defaultTextColor
        z: 1

        Label {
            text: (parent.width > 0) ? "Function parameters" : ""
            font.family: Flat.FlatStyle.fontFamily
            font.pixelSize: Math.round(12 * Flat.FlatStyle.scaleFactor)// * width / 200)
            renderType: Text.QtRendering
            color: "white"
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }



    Flickable {
        id: flickable
        width: parent.width
        anchors.top: settingsTitleBar.bottom
        anchors.topMargin: 40
        anchors.bottom: parent.bottom
        contentHeight: 500
        z: 0

        Item {
            id: controlsMainRect
            //            anchors.top: controlsTitleBar.bottom
            //            anchors.topMargin: 40
            width: parent.width

            Label {
                id: label1
                text: (parent.width > 0) ? "g(x) = " : ""
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
        anchors.left: parent.left
        visible: settingsRect.width > 0
    }
}
