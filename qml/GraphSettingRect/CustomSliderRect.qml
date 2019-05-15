import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2

Rectangle {
    id: rect

    property alias sliderValue: slider.value
    property int maxValue: 20

    width: definedWidth
    height: definedHeight
    
    Slider {
        id: slider
        width: rect.width / 2
        from: 1
        to: maxValue
        stepSize: 1
        anchors.verticalCenter: parent.verticalCenter
    }
    
    Item {
        height: rect.height
        anchors.left: slider.right
        anchors.right: parent.right
        
        Label {
            text: slider.value
            font.pixelSize: 40
            anchors.centerIn: parent
        }
    }
}
