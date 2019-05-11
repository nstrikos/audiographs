import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.3

Rectangle {
    id: rect3

    property alias input5: input5
    property alias input6: input6

    visible: false
    anchors {
        top: parent.top
        bottom: parent.bottom
        right: parent.right
        left: buttonsRect.right
    }
    color: "cyan"
    
    Column {
        
        TextEditLayout {
            id: input5
            x: 8; y: 8
            width: 96; height: 20
            //focus: true
            text: "Text Input 5"
            KeyNavigation.tab: input6
            Accessible.role: Accessible.EditableText
            //Accessible.name: "Input"
            Accessible.description: "Insert fifth value"
            onActiveFocusChanged: {
                if (activeFocus)
                    androidClient.speak("Input 5 " + text)
            }
        }
        
        TextEditLayout {
            id: input6
            x: 8; y: 36
            width: 96; height: 20
            text: "Text Input 6"
            KeyNavigation.tab: buttonsRect.parametersButton
            Accessible.role: Accessible.EditableText
            //Accessible.name: "Input"
            Accessible.description: "Insert sixth value"
            onActiveFocusChanged: {
                if (activeFocus)
                    androidClient.speak("Input 6 " + text)
            }
        }
    }
}
