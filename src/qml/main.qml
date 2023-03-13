import QtQuick 2.12
import QtQuick.Window 2.12
import Qt.labs.settings 1.1
import QtQuick.Dialogs 1.1

//import QtQml.StateMachine 1.0 as DSM

import "ControlsRect"
import "GraphRect"
import "SettingsRect"

Window {
    id: window
    visible: true

    //on android setting width and height results in
    //not showing correctly the application
    //    width: Qt.platform.os === "android" ? 320 : 1024//: Screen.width
    //    height: Qt.platform.os === "android" ? 350 : 768//Screen.height
    minimumWidth: 320
    minimumHeight: 320
    title: qsTr("Audiographs")

    property bool anchorToLeft: undefined

    //    property alias settingsRect: settingsRect
    property alias graphRect: graphRect
    property alias controlsRect: controlsRect

    property bool canZoomDrag: false

    property string errorString

    Settings {
        property alias x: window.x
        property alias y: window.y
        property alias width: window.width
        property alias height: window.height
    }

    ControlsRect {
        id: controlsRect
    }

    //    ControlsButton {
    //        id: controlsButton
    //    }

    GraphRect {
        id: graphRect
    }

    //    SettingsButton {
    //        id: settingsButton
    //    }

    //    SettingsRect {
    //        id: settingsRect
    //    }

    AnchorChangeState {
        id: anchorChangeState
    }

    Component.onCompleted: {
        setAnchor()
        if (anchorToLeft)
            anchorChangeState.state = 'state1'
        else
            anchorChangeState.state = 'state4'

        controlsRect.textInput.forceActiveFocus()
    }

    onWidthChanged: setAnchor()
    onHeightChanged: setAnchor()

    function setAnchor() {
        if (width >= height)
            anchorToLeft = true
        else
            anchorToLeft = false

    }
    onAnchorToLeftChanged: anchorChangeState.anchorChanged()

    function setColor() {
        controlsRect.color = !parameters.invertTheme ? "white" : "black"
        controlsRect.fontColor = parameters.invertTheme ? "white" : "black"
    }

    Shortcuts {
        id: shortcuts
    }

    //    StateMachine {
    //        id: stateMachine
    //    }

    //    Connections {
    //        target: functionExpression
    //        onNewGraph: newGraph()
    //        onNewInputValues: controlsRect.newInputValues(minX, maxX, minY, maxY)
    //        onMovingPointFinished: stopAudio()
    //        onInterestingPointStopped: interestingPointStopped()
    //        onError: error()
    //    }

    Connections {
        target: qmlConnector
        function onQmlInitialStateActivated() {
            initialStateActivated()
        }
    }

    Connections {
        target: qmlConnector
        function onQmlEvaluateStateActivated() {
            evaluateStateActivated()
        }
    }

    Connections {
        target: qmlConnector
        function onQmlUpdateGraph(points, minX, maxX, minY, maxY) {
            graphRect.minX = minX
            graphRect.maxX = maxX
            graphRect.minY = minY
            graphRect.maxY = maxY
            qmlConnector.newGraph()
        }
    }

    Connections {
        target: qmlConnector
        function onQmlGraphReadyStateActivated() {
            graphReadyStateActivated()
        }
    }

    Connections {
        target: qmlConnector
        function onQmlPlaySoundStateActivated() {
            playSoundStateActivated()
        }
    }

    Connections {
        target: qmlConnector
        function onQmlPlaySoundStateDeactivated() {
            playSoundStateDeactivated()
        }
    }

    Connections {
        target: qmlConnector
        function onQmlInterestingPointStateActivated() {
            interestingPointStateActivated()
        }
    }

    Connections {
        target: qmlConnector
        function onQmlInterestingPointStateDeactivated() {
            interestingPointStateDeactivated()
        }
    }

    Connections {
        target: qmlConnector
        function onQmlInterestingPointStoppedStateActivated() {
            interestingPointStoppedStateActivated()
        }
    }

    Connections {
        target: qmlConnector
        function onQmlExploreStateActivated() {
            exploreStateActivated()
        }
    }

    Connections {
        target: qmlConnector
        function onQmlExploreStateDeactivated() {
            exploreStateDeactivated()
        }
    }

    Connections {
        target: qmlConnector
        function onQmlNewInputValues(minX, maxX, minY, maxY) {
            controlsRect.newInputValues(minX, maxX, minY, maxY)
        }
    }

    Connections {
        target: qmlConnector
        function onQmlAudioFinished() {
            stopAudio()
        }
    }

    Connections {
        target: qmlConnector
        function onQmlInterestingPointFinished() {
            interestingPointFinished()
        }
    }

    Connections {
        target: qmlConnector
        function onQmlErrorDisplayStateActivated() {
            errorDisplayStateActivated()
        }
    }

    Connections {
        target: qmlConnector
        function onQmlError(error) {
            qmlConnector.setDerivativeMode(0)
            window.graphRect.pointView.clear()
            window.graphRect.derivativeView.setUpdate(false);
            window.graphRect.graphCanvas.updateCanvas(-10, 10, -10, 10)
            disableControls()
            errorString = error
            qmlConnector.functionError()
        }
    }

    function showError(errorString) {
        errorDialog.visible = true
    }

    function initialStateActivated()
    {
        console.log("initial state activated")
        qmlConnector.setDerivativeMode(0)
        window.graphRect.pointView.clear()
        window.graphRect.derivativeView.setUpdate(false);
        window.graphRect.derivativeView.visible = false
        window.graphRect.graphCanvas.updateCanvas(-10, 10, -10, 10)
        disableControls()
    }

    function evaluateStateActivated()
    {
        console.log("evaluate state activated")
        disableControls()
        qmlConnector.setDerivativeMode(0)
        window.graphRect.derivativeView.setUpdate(false);
        window.graphRect.derivativeView.visible = false
        qmlConnector.calculate(controlsRect.textInput.text,
                               controlsRect.textInput2.text,
                               controlsRect.textInput3.text,
                               controlsRect.textInput4.text,
                               controlsRect.textInput5.text)
    }

    function graphReadyStateActivated()
    {
        console.log("graph ready state activated")
        enableControls()
        controlsRect.startSoundButton.text = qsTr("Start sound")
        graphRect.updateCanvas()
        window.graphRect.pointView.clear()
    }

    function playSoundStateActivated()
    {
        console.log("play sound state activated")
        //ui->startSoundPushButton->setText(tr("Enter - Stop sound"));
        //ui->renderArea->enableCurrentPoint();
        controlsRect.startSoundButton.text = qsTr("Stop sound")
        enableControls();
        qmlConnector.playSound();
    }

    function playSoundStateDeactivated()
    {
        console.log("play sound state deactivated")
        controlsRect.startSoundButton.text = qsTr("Start sound")
        //ui->renderArea->disableCurrentPoint();
        qmlConnector.stopSound();
    }

    function interestingPointStateActivated()
    {
        console.log("interesting point state activated")
        controlsRect.startSoundButton.text = qsTr("Stop sound")
        //ui->renderArea->disableCurrentPoint();
    }

    function interestingPointStateDeactivated()
    {
        console.log("interesting point state deactivated")
        controlsRect.startSoundButton.text = qsTr("Start sound")
        qmlConnector.stopSound()
        //ui->renderArea->disableCurrentPoint();
    }

    function interestingPointStoppedStateActivated()
    {
        console.log("interesting point stopped state activated")
        controlsRect.startSoundButton.text = qsTr("Start sound")
        //ui->renderArea->disableCurrentPoint();
    }

    function exploreStateActivated()
    {
        console.log("explore state activated")
        //ui->renderArea->disableCurrentPoint();
    }

    function errorDisplayStateActivated()
    {
        console.log("error display state activated")
        errorDialog.visible = true

    }

    MessageDialog {
        id: errorDialog
        title: "Error"
        text: errorString
        onAccepted: qmlConnector.errorAccepted()
        Component.onCompleted: visible = false
        //Accessible.name: qsTr("Error")
        //Accessible.description: qsTr("Error")
    }

    function normalDerivative()
    {
        qmlConnector.setDerivativeMode(0)
        window.graphRect.derivativeView.visible = false
        window.graphRect.derivativeView.setUpdate(false)
        textToSpeech.speak("Normal derivative mode");
    }

    function firstDerivative()
    {
        window.graphRect.derivativeView.visible = true
        window.graphRect.derivativeView.setUpdate(true)
        qmlConnector.setDerivativeMode(1)
        textToSpeech.speak("First derivative mode");
    }

    function secondDerivative()
    {
        window.graphRect.derivativeView.visible = true
        window.graphRect.derivativeView.setUpdate(true)
        qmlConnector.setDerivativeMode(2)
        textToSpeech.speak("Second derivative mode");
    }

    function exploreStateDeactivated()
    {
        console.log("explore state deactivated")
        //ui->renderArea->disableCurrentPoint();
    }

    function disableControls()
    {
        controlsRect.disable()
        controlsRect.startSoundButton.enabled = false
        window.canZoomDrag = false
    }

    function enableControls()
    {
        controlsRect.enable()
        controlsRect.startSoundButton.enabled = true
        window.canZoomDrag = true
    }
}
