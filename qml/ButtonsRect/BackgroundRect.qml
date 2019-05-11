import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5

import "../js/ButtonFunctions.js" as ButtonFunctions

Rectangle {
    implicitHeight: 100
    radius: 10
    border.color: ButtonFunctions.setBorderColor()
    color: isActive ? "lightblue": "white"
    border.width: 5
}
