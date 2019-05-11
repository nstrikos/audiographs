import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

RowLayout {

    property alias text: label.text
    property bool isActive: false
    property bool isPressed: false

    width: parent.width

    Rectangle {
        Layout.minimumWidth: 150
        Label {
            id: label
            text: text
            font.pixelSize: 20
            anchors.centerIn: parent
        }
    }

    Button {
        id: button
        width: parent.width
        Layout.fillWidth: true

        contentItem: CustomText {
            id: buttonText
        }

        background: BackgroundRect {
        }

        onClicked: {
            isPressed = !isPressed
            speak()
        }

        onFocusChanged: {
            if (activeFocus) {
                isActive = true
                speak()
            }
            else {
                isActive = false
            }
        }

        Keys.onBacktabPressed: {
            stepInput.forceActiveFocus()
        }

        function speak() {
            var state = qsTr("Off")
            if (isPressed)
                state = qsTr("On")
            androidClient.speak(qsTr("Check button") + " " + label.text + " " + state)
        }

        Component.onCompleted: {
            isActive = false
            isPressed = false
        }
    }

    onActiveFocusChanged: {
        if (activeFocus)
            button.forceActiveFocus()
    }

    Keys.onEscapePressed:  parametersRect.escapePressed()

    Keys.onBackPressed: parametersRect.escapePressed()
}
