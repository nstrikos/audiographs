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

    property int duration: 10
    property int minFreq: 200
    property int maxFreq: 2000

    Rectangle {
        id: settingsTitleBar
        width: parent.width
        height: 54 * Flat.FlatStyle.scaleFactor
        color: Flat.FlatStyle.defaultTextColor
        z: 1

        Label {
            text: (parent.width > 0) ? "Sound parameters" : ""
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
        contentHeight: 400
        z: 0

        Item {
            id: controlsMainRect
            //            anchors.top: controlsTitleBar.bottom
            //            anchors.topMargin: 40
            width: parent.width

            Label {
                id: label1
                text: (parent.width > 0) ? "Duration : " : ""
                anchors.left: parent.left
                anchors.leftMargin: 5
                width: 100
            }

            SpinBox {
                id: textInput
                anchors.left: label1.right
                anchors.leftMargin: 10
                anchors.right: parent.right
                anchors.rightMargin: 10
                anchors.verticalCenter: label1.verticalCenter
                height: 50
                value: 10
                from: 10
                to: 120
                onValueChanged: duration = value
            }

            Label {
                id: label2
                text: (parent.width > 0) ? "min frequency : " : ""
                anchors.left: parent.left
                anchors.leftMargin: 5
                anchors.top: textInput.bottom
                anchors.topMargin: 40
                width: 100
            }

            SpinBox {
                id: textInput2
                anchors.left: label2.right
                anchors.leftMargin: 10
                anchors.verticalCenter: label2.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 10
                height: 50
                property bool active: true
                value: 200
                from: 200
                to: 4000
                stepSize: 100
                onValueChanged: minFreq = value
            }

            Label {
                id: label3
                text: (parent.width > 0) ? "max frequency : " : ""
                anchors.left: parent.left
                anchors.leftMargin: 5
                anchors.top: textInput2.bottom
                anchors.topMargin: 40
                width: 100
            }

            SpinBox {
                id: textInput3
                anchors.left: label3.right
                anchors.leftMargin: 10
                anchors.verticalCenter: label3.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 10
                height: 50
                property bool active: true
                value: 2000
                from: 200
                to: 4000
                stepSize: 100
                onValueChanged: maxFreq = value
            }

            Label {
                id: label4
                text: (parent.width > 0) ? "Select mode : " : ""
                anchors.left: parent.left
                anchors.leftMargin: 5
                anchors.top: textInput3.bottom
                anchors.topMargin: 40
                width: 100
            }



            Rectangle {
                anchors.top: label4.bottom
                anchors.topMargin: 10
                border.color: "gray"
                width: parent.width
                height: 150
                ColumnLayout {
                    RadioButton {
                        checked: true
                        text: qsTr("First")
                        onCheckedChanged: modeChanged(0)
                    }
                    RadioButton {
                        text: qsTr("Second")
                        onCheckedChanged: modeChanged(1)
                    }
                    RadioButton {
                        text: qsTr("Third")
                        onCheckedChanged: modeChanged(2)
                    }
                }
            }
        }
    }

    function modeChanged(value) {
        window.mode = value
    }






    BeautifyRect {
        anchors.left: parent.left
        visible: settingsRect.width > 0
    }
}
