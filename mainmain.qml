import QtQuick 2.0
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12


import "qml/GraphRect"
import "qml/MainGrid"

Window {
    id: window
    visible: true
    width: 320
    height: 350
    minimumWidth: 320
    minimumHeight: 320
    title: qsTr("Audio graphs")

    property var expression
    property bool anchorToLeft

    GraphRect {
        id: graphRect
        height: parent.height
        visible: true
        anchors.right: settingsRect.left
        anchors.left: controlsRect.right
        z: 10
//        layer.enabled: true
//        layer.samples: 256
    }

    ControlsButton {
        id: controlsButton
    }

    SettingsButton {
        id: settingsButton
    }

    ControlsRect {
        id: controlsRect
        width: window.width / 3
        shown: true
    }

    SettingsRect {
        id: settingsRect
    }

    onWidthChanged: setAnchor()
    onHeightChanged: setAnchor()

    function setAnchor() {

        if (width >= height)
            anchorToLeft = true
        else
            anchorToLeft = false

        if (anchorToLeft) {
            controlsRect.height = window.height
            controlsRect.anchors.top = graphRect.top
            graphRect.height = window.height
            graphRect.anchors.left = controlsRect.right


            if (controlsRect.shown == true)
                controlsRect.width = window.width / 3
            else
                controlsRect.width = 0

            if (settingsRect.shown == true)
                settingsRect.width = window.width / 3
        } else {

            if (controlsRect.shown == true) {
                graphRect.height = window.height / 2
                graphRect.anchors.left = window.left
                graphRect.width = window.width
                controlsRect.height = window.height / 2
                controlsRect.anchors.top = graphRect.bottom
                controlsRect.width = window.width
            } else {
                graphRect.height = window.height
                graphRect.anchors.left = window.left
                graphRect.width = window.width
                controlsRect.height = 0
                controlsRect.anchors.top = graphRect.bottom
                controlsRect.width = window.width
            }
        }
    }

    Connections {
        target: myfunction
        onUpdate: {
            graphRect.updatePoints()
            graphRect.draw()
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

    Component.onCompleted: {
        setAnchor()
//        myfunction.calculate("sin(x)",
//                             -10,
//                             10,
//                             100)
    }
}
