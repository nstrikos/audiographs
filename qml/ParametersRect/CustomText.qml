import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

Text {
    id: buttonText
    text: isPressed ? "On" : "Off"
    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
    font.pixelSize: 20
    anchors.fill: parent
    antialiasing: true
}
