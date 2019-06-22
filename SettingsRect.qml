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
    
    Behavior on width {
        NumberAnimation { duration: 300 }
    }
    
    Rectangle {
        id: settingsTitleBar
        width: parent.width
        height: 54 * Flat.FlatStyle.scaleFactor
        color: Flat.FlatStyle.defaultTextColor
        
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
    
    
    Item {
        anchors.top: settingsTitleBar.bottom
        anchors.topMargin: 40
        width: parent.width
        
        
        Label {
            id: label2
            text: (parent.width > 0) ? "Duration: " : ""
            //                anchors.top: controlsTitleBar.bottom
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.verticalCenter: parent.verticalCenter
            width: 100
            //height: 50
        }
        
        
        
        TextField {
            id: textInput2
            //                Layout.fillWidth: true
            //                anchors.topMargin: 20
            anchors.left: label2.right
            anchors.right:  parent.right
            anchors.rightMargin: 5
            anchors.verticalCenter: parent.verticalCenter
            //width: parent.width - label2.width - 20
            
            placeholderText: (parent.width > 0) ? "Duration in seconds" : ""
            height: 50
            //                width: parent.width - 50
            //                anchors.right: parent.right
            onTextChanged: myparameters.duration = text
            
        }
    }

    BeautifyRect {
        anchors.left: parent.left
        visible: settingsRect.width > 0
    }
}
