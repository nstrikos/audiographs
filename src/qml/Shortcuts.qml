import QtQuick 2.0

import QtQuick 2.12

Item {
//    Shortcut {
//        sequence: "Esc"
//        onActivated: close()
//    }
    Shortcut {
        sequence: "Return"
        onActivated: {
            qmlConnector.playPressed()
        }
    }
    Shortcut {
        sequence: "Ctrl+N"
        onActivated: {
            controlsRect.textInput.clear()
            controlsRect.textInput.forceActiveFocus()
            textToSpeech.speak(qsTr("Function expression"))
            qmlConnector.evaluate()
        }
    }
    Shortcut {
        sequence: "Ctrl+X"
        onActivated: {
            qmlConnector.sayX()
        }
    }
    Shortcut {
        sequence: "Ctrl+Y"
        onActivated: {
            qmlConnector.sayY()
        }
    }
    Shortcut {
        sequence: StandardKey.MoveToPreviousPage
        onActivated: {
            qmlConnector.nextPoint()
        }
    }
    Shortcut {
        sequence: StandardKey.MoveToNextPage
        onActivated: {
            qmlConnector.previousPoint()
        }
    }
    Shortcut {
        sequence: "Ctrl+Left"
        onActivated: {
            qmlConnector.previousPointInterest()
        }
    }
    Shortcut {
        sequence: "Ctrl+Right"
        onActivated: {
            qmlConnector.nextPointInterest()
        }
    }
    Shortcut {
        sequence: "Shift+Left"
        onActivated: {
            qmlConnector.previousFast()
        }
    }
    Shortcut {
        sequence: "Shift+Right"
        onActivated: {
            qmlConnector.nextFast()
        }
    }
    Shortcut {
        sequence: StandardKey.MoveToStartOfLine
        onActivated: {
            qmlConnector.firstPoint()
        }
    }
    Shortcut {
        sequence: StandardKey.MoveToEndOfLine
        onActivated: {
            qmlConnector.lastPoint()
        }
    }
    Shortcut {
        sequence: "Ctrl+D"
        onActivated: {
            qmlConnector.sayDerivative()
        }
    }

    Shortcut {
        sequence: "Ctrl+0"
        onActivated: {
            window.normalDerivative()
        }
    }

    Shortcut {
        sequence: "Ctrl+1"
        onActivated: {
            window.firstDerivative()
        }
    }

    Shortcut {
        sequence: "Ctrl+2"
        onActivated: {
            window.secondDerivative()
        }
    }

    Shortcut {
        sequence: "Ctrl+["
        onActivated: {
            qmlConnector.decStep()
        }
    }
    Shortcut {
        sequence: "Ctrl+]"
        onActivated: {
            qmlConnector.incStep()
        }
    }
    Shortcut {
        sequence: "F2"
        onActivated: {
            window.controlsRect.selfVoiceFocusScope.selfVoiceCheckBox.checked = !window.controlsRect.selfVoiceFocusScope.selfVoiceCheckBox.checked
        }
    }
    Shortcut {
        sequence: "F3"
        onActivated: {
            window.controlsRect.useNotesFocusScope.useNotesCheckBox.checked = !window.controlsRect.useNotesFocusScope.useNotesCheckBox.checked
        }
    }
    Shortcut {
        sequence: "F4"
        onActivated: {
            window.controlsRect.useNegativeNotesFocusScope.useDifferentNotesCheckBox.checked= !window.controlsRect.useNegativeNotesFocusScope.useDifferentNotesCheckBox.checked
        }
    }
    Shortcut {
        sequence: "F9"
        onActivated: {
            var value = window.controlsRect.precisionSpinbox.value
            value--;
            if (value < 0)
                value = 0;
            window.controlsRect.precisionSpinbox.value = value
        }
    }
    Shortcut {
        sequence: "F10"
        onActivated: {
            var value = window.controlsRect.precisionSpinbox.value
            value++;
            if (value > 5)
                value = 5;
            window.controlsRect.precisionSpinbox.value = value
        }
    }
}
