import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2

Rectangle {
    id: rect

    property alias sliderValue: slider.value
    property int maxValue: 20
    property string text: ""

    width: definedWidth
    height: definedHeight
    
    Slider {
        id: slider
        width: rect.width / 2
        from: 1
        to: maxValue
        stepSize: 1
        anchors.verticalCenter: parent.verticalCenter
        onFocusChanged: speak()
        onValueChanged: speak()

        function speak() {
            if (activeFocus)
                texttospeech.speak(rect.text + " " + slider.value)
        }
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
