import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5

import "qml/"
import "qml/ButtonsRect"
import "qml/ParametersRect"
import "qml/GraphRect"

Window {
    visible: true
    width: 640
    height: 480
    minimumWidth: 450
    title: qsTr("Sound graphs")

    ButtonsRect {
        id: buttonsRect
    }

    ParametersRect {
        id: parametersRect
    }

    GraphRect {
        id: graphRect
    }

    Rect2 {
        id: rect2
    }

    Rect3 {
        id: rect3
    }

    Connections {
        target: myfunction
        onUpdate: graphRect.updatePoints()
        onError: console.log(err)
    }

    Component.onCompleted: {
        parametersRect.visible = true
        graphRect.visible = false
        rect2.visible = false
        rect3.visible = false
    }
}
