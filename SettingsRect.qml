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
    property bool useNotes: checkBox.checked

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
        contentHeight: 1500
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
                from: 100
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
                id: checkBoxlabel
                text: (parent.width > 0) ? "Use notes : " : ""
                anchors.left: parent.left
                anchors.leftMargin: 5
                anchors.top: textInput3.bottom
                anchors.topMargin: 40
                width: 100
            }

            CheckBox {
                id: checkBox
                anchors.left: checkBoxlabel.right
                anchors.leftMargin: 10
                anchors.verticalCenter: checkBoxlabel.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 10
                height: 50
                property bool active: true
                //value: 2000
                //from: 200
                //to: 4000
                //stepSize: 100
                //onValueChanged: maxFreq = value
            }

            Label {
                id: f0label
                text: (parent.width > 0) ? "f0 frequency : " : ""
                anchors.left: parent.left
                anchors.leftMargin: 5
                anchors.top: checkBox.bottom
                anchors.topMargin: 40
                width: 100
            }

            SpinBox {
                id: f0textInput
                anchors.left: f0label.right
                anchors.leftMargin: 10
                anchors.verticalCenter: f0label.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 10
                height: 50
                property bool active: true
                value: 100
                from: 0
                to: 100
                stepSize: 1
                onValueChanged: graphRect.curveMovingPoint.f0 = value / 100.0;
            }

            Label {
                id: f1label
                text: (parent.width > 0) ? "f1 frequency : " : ""
                anchors.left: parent.left
                anchors.leftMargin: 5
                anchors.top: f0textInput.bottom
                anchors.topMargin: 40
                width: 100
            }

            SpinBox {
                id: f1textInput
                anchors.left: f1label.right
                anchors.leftMargin: 10
                anchors.verticalCenter: f1label.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 10
                height: 50
                property bool active: true
                value: 0
                from: 0
                to: 100
                stepSize: 1
                onValueChanged: graphRect.curveMovingPoint.f1 = value / 100.0;
            }

            Label {
                id: f2label
                text: (parent.width > 0) ? "f2 frequency : " : ""
                anchors.left: parent.left
                anchors.leftMargin: 5
                anchors.top: f1textInput.bottom
                anchors.topMargin: 40
                width: 100
            }

            SpinBox {
                id: f2textInput
                anchors.left: f2label.right
                anchors.leftMargin: 10
                anchors.verticalCenter: f2label.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 10
                height: 50
                property bool active: true
                value: 0
                from: 0
                to: 100
                stepSize: 1
                onValueChanged: graphRect.curveMovingPoint.f2 = value / 100.0;
            }

            Label {
                id: f3label
                text: (parent.width > 0) ? "f3 frequency : " : ""
                anchors.left: parent.left
                anchors.leftMargin: 5
                anchors.top: f2textInput.bottom
                anchors.topMargin: 40
                width: 100
            }

            SpinBox {
                id: f3textInput
                anchors.left: f3label.right
                anchors.leftMargin: 10
                anchors.verticalCenter: f3label.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 10
                height: 50
                property bool active: true
                value: 0
                from: 0
                to: 100
                stepSize: 1
                onValueChanged: graphRect.curveMovingPoint.f3 = value / 100.0;
            }

            Label {
                id: f4label
                text: (parent.width > 0) ? "f4 frequency : " : ""
                anchors.left: parent.left
                anchors.leftMargin: 5
                anchors.top: f3textInput.bottom
                anchors.topMargin: 40
                width: 100
            }

            SpinBox {
                id: f4textInput
                anchors.left: f4label.right
                anchors.leftMargin: 10
                anchors.verticalCenter: f4label.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 10
                height: 50
                property bool active: true
                value: 0
                from: 0
                to: 100
                stepSize: 1
                onValueChanged: graphRect.curveMovingPoint.f4 = value / 100.0;
            }

            Label {
                id: f5label
                text: (parent.width > 0) ? "f5 frequency : " : ""
                anchors.left: parent.left
                anchors.leftMargin: 5
                anchors.top: f4textInput.bottom
                anchors.topMargin: 40
                width: 100
            }

            SpinBox {
                id: f5textInput
                anchors.left: f5label.right
                anchors.leftMargin: 10
                anchors.verticalCenter: f5label.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 10
                height: 50
                property bool active: true
                value: 0
                from: 0
                to: 100
                stepSize: 1
                onValueChanged: graphRect.curveMovingPoint.f5 = value / 100.0;
            }

            Label {
                id: f6label
                text: (parent.width > 0) ? "f6 frequency : " : ""
                anchors.left: parent.left
                anchors.leftMargin: 5
                anchors.top: f5textInput.bottom
                anchors.topMargin: 40
                width: 100
            }

            SpinBox {
                id: f6textInput
                anchors.left: f6label.right
                anchors.leftMargin: 10
                anchors.verticalCenter: f6label.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 10
                height: 50
                property bool active: true
                value: 0
                from: 0
                to: 100
                stepSize: 1
                onValueChanged: graphRect.curveMovingPoint.f6 = value / 100.0;
            }

            Label {
                id: f7label
                text: (parent.width > 0) ? "f7 frequency : " : ""
                anchors.left: parent.left
                anchors.leftMargin: 5
                anchors.top: f6textInput.bottom
                anchors.topMargin: 40
                width: 100
            }

            SpinBox {
                id: f7textInput
                anchors.left: f7label.right
                anchors.leftMargin: 10
                anchors.verticalCenter: f7label.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 10
                height: 50
                property bool active: true
                value: 0
                from: 0
                to: 100
                stepSize: 1
                onValueChanged: graphRect.curveMovingPoint.f7 = value / 100.0;
            }

            Label {
                id: f8label
                text: (parent.width > 0) ? "f8 frequency : " : ""
                anchors.left: parent.left
                anchors.leftMargin: 5
                anchors.top: f7textInput.bottom
                anchors.topMargin: 40
                width: 100
            }

            SpinBox {
                id: f8textInput
                anchors.left: f8label.right
                anchors.leftMargin: 10
                anchors.verticalCenter: f8label.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 10
                height: 50
                property bool active: true
                value: 0
                from: 0
                to: 100
                stepSize: 1
                onValueChanged: graphRect.curveMovingPoint.f8 = value / 100.0;
            }

            Label {
                id: f9label
                text: (parent.width > 0) ? "f9 frequency : " : ""
                anchors.left: parent.left
                anchors.leftMargin: 5
                anchors.top: f8textInput.bottom
                anchors.topMargin: 40
                width: 100
            }

            SpinBox {
                id: f9textInput
                anchors.left: f9label.right
                anchors.leftMargin: 10
                anchors.verticalCenter: f9label.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 10
                height: 50
                property bool active: true
                value: 0
                from: 0
                to: 100
                stepSize: 1
                onValueChanged: graphRect.curveMovingPoint.f9 = value / 100.0;
            }

            Label {
                id: f10label
                text: (parent.width > 0) ? "f10 frequency : " : ""
                anchors.left: parent.left
                anchors.leftMargin: 5
                anchors.top: f9textInput.bottom
                anchors.topMargin: 40
                width: 100
            }

            SpinBox {
                id: f10textInput
                anchors.left: f10label.right
                anchors.leftMargin: 10
                anchors.verticalCenter: f10label.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 10
                height: 50
                property bool active: true
                value: 0
                from: 0
                to: 100
                stepSize: 1
                onValueChanged: graphRect.curveMovingPoint.f10 = value / 100.0;
            }

            Label {
                id: label4
                text: (parent.width > 0) ? "Select mode : " : ""
                anchors.left: parent.left
                anchors.leftMargin: 5
                anchors.top: f10textInput.bottom
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
