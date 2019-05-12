import QtQuick 2.5
import QtQuick.Controls 1.4

Rectangle {
    id: textInputFrame

    property real value: 0
    property alias text: textInput.text

    width: parent.width
    height: 40
    border { color: "black"; width: 2}
    radius: 10
    antialiasing: true
    color: "darkGray"

    TextInput {
        id: textInput
        anchors.fill: parent
        anchors.margins: 5
        font.pixelSize: height - 2
        verticalAlignment: TextInput.AlignVCenter
        clip: true
        onTextChanged: {
            value = parseFloat(text)
        }
    }
}
