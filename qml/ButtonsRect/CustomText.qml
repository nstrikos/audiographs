import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5

import "../js/ButtonFunctions.js" as ButtonFunctions

Text {

    property int textSize: 25

    id: buttonText
    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
    font.pixelSize: textSize
    color: ButtonFunctions.setTextColor()
    anchors.fill: parent
    antialiasing: true
}
