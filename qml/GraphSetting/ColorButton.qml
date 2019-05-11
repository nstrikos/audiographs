import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import "../js/ButtonFunctions.js" as ButtonFunctions
import "../ButtonsRect"

Button {
    id: root
    width: parent.width
    property bool isActive: false
    property bool isPressed: false
    property int textSize: 25
    property color mycolor

    focus: true
    Keys.onBackPressed: {
        graphSettingRect.visible = false
        grid.visible = true
        graphSettingsButton.forceActiveFocus()
    }
    Keys.onEscapePressed: {
        graphSettingRect.visible = false
        grid.visible = true
        grid.graphSettingsButton.forceActiveFocus()
    }

    Accessible.name: "My button"

    background: Rectangle {
        implicitHeight: 100
        radius: 10
        border.color: ButtonFunctions.setBorderColor()
        color: mycolor
        border.width: 5
    }

    onFocusChanged: ButtonFunctions.focusChanged()
}
