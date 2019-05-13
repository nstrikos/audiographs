import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5

import "qml/ButtonsRect"
import "qml/ParametersRect"
import "qml/GraphRect"
import "qml/GraphSetting"
import "qml/"

Window {
    id: window
    visible: true
    width: 640
    height: 550
    minimumWidth: 480
    minimumHeight: 640
    title: qsTr("Sound graphs")

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
