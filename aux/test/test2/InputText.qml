import QtQuick 2.9
import QtQuick.Controls 1.4

TextInput {
    property real value: 0

    anchors.verticalCenter: parent.verticalCenter
    width: parent.width
    font.pixelSize: 18
    antialiasing: true
    onTextChanged: value = parseFloat(text)
}
