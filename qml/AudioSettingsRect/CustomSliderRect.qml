import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2

Rectangle {
    id: rect

    property alias sliderValue: slider.value
    property int minValue: 1
    property int maxValue: 20
    property int step: 1
    property string text: ""

    //width: 200//definedWidth
    height: definedHeight

    function setFocus() {
        slider.forceActiveFocus()
    }
    
    Slider {
        id: slider
        width: parent.width - label.width - 10 //rect.width / 2
        from: minValue
        to: maxValue
        stepSize: step
        anchors.verticalCenter: parent.verticalCenter
        Accessible.name: rect.text + " " + qsTr("slider") + " " + slider.value
//        Accessible.role: Accessible.Slider
        onFocusChanged: speak()
        onValueChanged: speak()

        function speak() {
            //if (activeFocus && window.talkSpeech)
            if (visible)
                texttospeech.speak(rect.text + " " + qsTr("slider") + " " + slider.value)
        }
    }
    
    Item {
        height: rect.height
        anchors.left: slider.right
        anchors.right: parent.right
        
        Label {
            id: label
            text: slider.value
            font.pixelSize: 40
            anchors.centerIn: parent
        }
    }
}
