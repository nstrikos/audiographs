import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5

import "../js/ButtonFunctions.js" as ButtonFunctions

Button {
    id: root
    width: parent.width
    property bool isActive: false
    property bool isPressed: false
    property string customText: "Text"
    property int textSize: 25

    Accessible.name: "My button"

    contentItem: CustomText {
        id: buttonText
        text: customText
        textSize: root.textSize
    }

    background: BackgroundRect {
    }

    onFocusChanged: ButtonFunctions.focusChanged()
}
