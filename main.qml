import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5

import "qml/MainGrid"

//import "qml/ButtonsRect"
import "qml/ParametersRect"
import "qml/SpeechSettingsRect"
import "qml/GraphRect"
import "qml/GraphSettingRect"
import "qml/SettingsOtherRect"
//import "qml/"

Window {
    id: window
    visible: true
    width: 640
    height: 550
    minimumWidth: 480
    minimumHeight: 640
    title: qsTr("Sound graphs")

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

        SpeechSettings {
            id: speechSettings
            width: parent.width
            height: parent.height
        }

        SettingsOther {
            id: settingsOther
        }
    }

    Connections {
        target: myfunction
        onUpdate: {
            graphRect.updatePoints()
            test.stop();
            test.start(parametersRect.functionText,
                       parametersRect.minimumXText,
                       parametersRect.maximumXText,
                       10,
                       200,
                       2000);
            graphRect.startPoints()
        }
        onError: console.log(err)
    }
}
