import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

Rectangle {
    implicitHeight: 50
    radius: 10
    border.color: isActive ? "red" : "gray"
    color: isPressed ? "lightblue": "lightgray"
    border.width: isActive ? 5 : 2
}
