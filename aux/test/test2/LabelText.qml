import QtQuick 2.9
import QtQuick.Controls 1.4


Text {
    id: labelText
    Accessible.role: Accessible.StaticText
    Accessible.name: text
    anchors.left: parent.left
    anchors.verticalCenter: parent.verticalCenter
    width: 100
    font.pixelSize: 18
    antialiasing: true
}
