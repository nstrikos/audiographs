import QtQuick 2.12
import QtQuick.Controls 2.12

import "../BeautityRect"
import "../"

Rectangle {
    id: controlsRect
    anchors.rightMargin: window.width / 4

    property bool active: true
    color : !parameters.invertTheme ? "white" : "black"
    property color fontColor: parameters.invertTheme ? "white" : "black"
    property color bgColor: !parameters.invertTheme ? "white" : "black"
    property color lightColor: parameters.invertTheme ? "yellow" : "blue"
    property bool invertTheme: parameters.invertTheme

    property alias selfVoiceFocusScope: controlRectFlickable.selfVoiceFocusScope
    property alias useNotesFocusScope: controlRectFlickable.useNotesFocusScope
    property alias useNegativeNotesFocusScope: controlRectFlickable.useDifferentNotesFocusScope
    property alias stopAtZeroFocusScope: controlRectFlickable.stopAtZeroFocusScope

    property alias startSoundButton: controlRectFlickable.startSoundButton
    property alias startSoundButtonFocusScope: controlRectFlickable.startSoundButtonFocusScope

    property alias precisionSpinbox: controlRectFlickable.precisionSpinbox

    property alias textInput: controlRectFlickable.textInput
    property alias textInput2: controlRectFlickable.textInput2
    property alias textInput3: controlRectFlickable.textInput3
    property alias textInput4: controlRectFlickable.textInput4
    property alias textInput5: controlRectFlickable.textInput5

    function disable()
    {
        controlRectFlickable.disable()
    }

    function enable()
    {
        controlRectFlickable.enable()
    }

    onInvertThemeChanged: {
        fontColor: parameters.invertTheme ? "white" : "black"
        bgColor = !parameters.invertTheme ? "white" : "black"
        lightColor = parameters.invertTheme ? "yellow" : "blue"
    }

    focus: true
//    Keys.onPressed: {
//        window.keyEvent(event)
//    }

    ControlsTitleBar {
        id: controlsTitleBar
    }

    ControlRectFlickable {
        id: controlRectFlickable
    }

    BeautifyRect {
    }

    function newInputValues(minX, maxX, minY, maxY) {
        active = false
        textInput2.text = minX
        textInput3.text = maxX
        textInput4.text = minY
        textInput5.text = maxY
        active = true
    }
}
