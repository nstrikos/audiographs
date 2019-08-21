import QtQuick 2.9
import QtQuick.Controls 1.4

Rectangle {
    id: subjectRect

    property alias text: inputText.text
    property alias inputText: inputText
    property var accessibleDescription: "Subject rectangle"
    property alias value: inputText.value

    Accessible.name: inputText.text
    Accessible.description: accessibleDescription

    anchors {
        top: parent.top
        bottom: parent.bottom
        right: parent.right
        //verticalCenter: parent.verticalCenter
        margins: 6
    }

    border {
        width: 1
        color: "black"
    }

    InputText {
        id: inputText
    }
}
