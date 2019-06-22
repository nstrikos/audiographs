import QtQuick 2.0
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12


import "qml/GraphRect"
import "qml/MainGrid"

Item {
    id: rect4
    height: 50
    width: 50
    
    SettingsIcon {
        width: 50
        height: 50
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 5
    }
    
    MouseArea {
        anchors.fill: parent
        onClicked: {
            if (myItem.state == 'state1' || myItem.state == 'state2')
                myItem.state = 'state3'
            else if (myItem.state == 'state3')
                myItem.state = 'state2'
            else if (myItem.state == 'state4' || myItem.state == 'state5')
                myItem.state = 'state6'
            else if (myItem.state == 'state6')
                myItem.state = 'state5'
        }
    }
}
