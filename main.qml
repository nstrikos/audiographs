import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5

import "qml/MainGrid"

//import "qml/ButtonsRect"
import "qml/ParametersRect"
import "qml/SpeechSettingsRect"
import "qml/GraphRect"
import "qml/AudioSettingsRect"
import "qml/GraphSettingRect"
import "qml/SettingsOtherRect"
//import "qml/"

Window {
    id: window
    visible: true
    width: 320
    height: 320
    minimumWidth: 320
    minimumHeight: 320
    title: qsTr("Audio graphs")

    property bool talkSpeech: false

    Item {
        anchors.fill: parent
        focus: true
        Keys.onEscapePressed: window.close()
        Keys.onBackPressed: window.close()

        MainGrid {
            id: grid
        }

        ParametersRect {
            id: parametersRect
        }

        GraphRect {
            id: graphRect
        }

        GraphSettingRect {
            id: graphSettingRect
        }

        AudioSettingsRect {
            id: audioSettingsRect
        }

        SpeechSettings {
            id: speechSettings
            width: parent.width
            height: parent.height
        }

        SettingsOtherRect {
            id: settingsOtherRect
        }
    }

    Connections {
        target: myfunction
        onUpdate: {
            graphRect.updatePoints()
//            test.stop();
//            test.start(parametersRect.functionText,
//                       parametersRect.minimumXText,
//                       parametersRect.maximumXText,
//                       myparameters.duration,
//                       myparameters.minFreq,
//                       myparameters.maxFreq);
//            graphRect.startPoints()
        }
        onError: console.log(err)
    }
}
