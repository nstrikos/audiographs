import QtQuick 2.9
import QtQuick.Controls 1.4


Rectangle {
    id: root

    property alias labelText: labelText.text
    property alias text: subjectRect.text
    property alias inputText: subjectRect.inputText
    property alias accessibleDescription: subjectRect.accessibleDescription
    property alias value: subjectRect.value

    width: parent.width
    height: 70

    LabelText {
        id: labelText
        text: labelText
    }

    SubjectRect {
        id: subjectRect
        anchors.left: labelText.right
    }
}

