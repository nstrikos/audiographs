import QtQuick 2.12
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

Button {
    id: button1
    text: "x"
    onPressed: {
        expression += text
        textToSpeech.speak(text)
    }
    Layout.fillWidth: true
    Layout.fillHeight: true
    onFocusChanged: {
        if (activeFocus)
            textToSpeech.speak(text)
    }
}
