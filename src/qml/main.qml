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
    property alias virtualKeyboard: virtualKeyboard
    property alias virtualNumericalKeyboard: virtualNumericalKeyboard

    property bool canZoomDrag: false

    property string errorString

    property var expressions: []

    Settings {
        id: settings
        property alias x: window.x
        property alias y: window.y
        property alias width: window.width
        property alias height: window.height
        property var recentFiles: []
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

    AnchorChangeState {
        id: anchorChangeState
    }

    VirtualKeyboard {
        id: virtualKeyboard
        anchors.fill: parent
        visible: false
        z: 11
    }

    VirtualNumericalKeyboard {
        id: virtualNumericalKeyboard
        anchors.fill: parent
        visible: false
        z: 11
    }

    MultiPointTouchArea {
        id: multipointTouchArea
        anchors.fill: parent
        z: 12
        mouseEnabled: true

        property int numPointsPressed: 0

        property int x1
        property int y1
        property int newX1
        property int newY1
        property real distance1
        property real angle1

        property int x2
        property int y2
        property int newX2
        property int newY2
        property real distance2
        property real angle2

        property string buttonsPressed: "no tap"

        touchPoints: [
            TouchPoint { id: point1 },
            TouchPoint { id: point2 }
        ]

        onPressed: {
            numPointsPressed++
            if (numPointsPressed === 1)
                buttonsPressed = "single tap"
            else if (numPointsPressed === 2)
                buttonsPressed = "double tap"
            x1 = point1.x
            y1 = point1.y
            x2 = point2.x
            y2 = point2.y
        }

        onReleased: {
            numPointsPressed--
            if (numPointsPressed == 0) {
                newX1 = point1.x
                newY1 = point1.y
                distance1 = Math.sqrt( (newX1 - x1) * (newX1 - x1) + (y1 - newY1) * (y1 - newY1) )
                angle1 = Math.atan2(y1 - newY1, newX1 - x1) * 180.0 / Math.PI
                newX2 = point2.x
                newY2 = point2.y
                distance2 = Math.sqrt( (newX2 - x2) * (newX2 - x2) + (y2 - newY2) * (y2 - newY2) )
                angle2 = Math.atan2(y2 - newY2, newX2 - x2) * 180.0 / Math.PI

                if (buttonsPressed === "single tap") {
                    if (distance1 > 50) {
                        if (angle1 < 25 && angle1 > -25)
                            window.right()
                        else if (  (angle1 < 180 && angle1 > 155)  || (angle1 > -180) && (angle1 < -155) )
                            window.left()
                        else if (  (angle1 < 100 && angle1 > 80)  )
                            window.up()
                        else if (  (angle1 < -80 && angle1 > -110)  )
                            window.down()
                        else if (  (angle1 < 65 && angle1 > 30)  )
                            window.upright()
                        else if (  (angle1 < 150 && angle1 > 115)  )
                            window.upleft()
                        else if (  (angle1 < -30 && angle1 > -65)  )
                            window.downright()
                        else if (  (angle1 < -115 && angle1 > -150)  )
                            window.downleft()

                    }
                    if (distance1 < 10) {
                        keyEmitter.keySpacePressed(window)
                    }

                } else if (buttonsPressed === "double tap") {
                    if (distance1 < 10 && distance2 < 10) {
                        keyEmitter.keyReturnPressed(window)
                    }
                    if (distance1 > 50 && distance2 > 50) {
                        if (angle1 < 25 && angle1 > -25) {
                            if (angle2 < 25 && angle2 > -25) {
                                window.doubleRight()
                            }
                        } else if ((angle1 < 180 && angle1 > 155)  || ( (angle1 > -180) && (angle1 < -155))) {
                            if ((angle2 < 180 && angle2 > 155)  || ( (angle2 > -180) && (angle2 < -155)))
                                window.doubleLeft()
                        } else if ((angle1 < 100 && angle1 > 80) ) {
                            if ((angle2 < 100 && angle2 > 80) )
                                window.doubleUp()
                        }
                    }
                }
                buttonsPressed = "no tap"
            }
        }
    }

    Component.onCompleted: {
        setAnchor()
        if (anchorToLeft)
            anchorChangeState.state = 'state1'
        else
            anchorChangeState.state = 'state4'

        controlsRect.textInput.forceActiveFocus()
        expressions = settings.recentFiles
        expressions = expressions.filter(e => e !== " ");
    }

    Component.onDestruction: {
        expressions.push(" ")
        settings.recentFiles = expressions
        settings.sync()
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

        //add expression to recent expressions
        var expression = controlsRect.textInput.text
        expressions = expressions.filter(e => e !== expression);
        expressions.push(expression)
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

    function keyboard(text) {
        controlsRect.visible = true
        controlsRect.textInput.text = text
        controlsRect.textInput.forceActiveFocus()
    }

    function numericalKeyboard(text, target) {
        controlsRect.visible = true
        if (target === "minimumX") {
            controlsRect.textInput2.text = text
            controlsRect.textInput2.forceActiveFocus()
        } else if (target === "maximumX") {
            controlsRect.textInput3.text = text
            controlsRect.textInput3.forceActiveFocus()
        } else if (target === "minimumY") {
            controlsRect.textInput4.text = text
            controlsRect.textInput4.forceActiveFocus()
        } else if (target === "maximumY") {
            controlsRect.textInput5.text = text
            controlsRect.textInput5.forceActiveFocus()
        }
    }

    function right()
    {
        keyEmitter.keyTabPressed(window)
    }

    function left()
    {
        keyEmitter.keyShiftTabPressed(window)
    }

    function up()
    {
        if (controlsRect.precisionSpinbox.activeFocus ||
                controlsRect.durationSpinbox.activeFocus  ||
                controlsRect.minFreqSpinbox.activeFocus   ||
                controlsRect.maxFreqSpinbox.activeFocus   ||
                controlsRect.lineWidthSpinbox.activeFocus ||
                controlsRect.highlightSizeSpinbox.activeFocus ||
                controlsRect.axesSizeSpinbox.activeFocus)
            keyEmitter.keyUpPressed(window)
        else
            keyEmitter.keyControlYPressed(window)
    }

    function down()
    {
        if (controlsRect.precisionSpinbox.activeFocus ||
                controlsRect.durationSpinbox.activeFocus  ||
                controlsRect.minFreqSpinbox.activeFocus   ||
                controlsRect.maxFreqSpinbox.activeFocus   ||
                controlsRect.lineWidthSpinbox.activeFocus ||
                controlsRect.highlightSizeSpinbox.activeFocus ||
                controlsRect.axesSizeSpinbox.activeFocus)
            keyEmitter.keyDownPressed(window)
        else
            keyEmitter.keyControlXPressed(window)
    }

    function upright()
    {
        keyEmitter.keyControlRightPressed(window)
    }

    function upleft()
    {
        keyEmitter.keyControlLeftPressed(window)
    }

    function downright()
    {
        keyEmitter.keyEndPressed(window)
    }

    function downleft()
    {
        keyEmitter.keyHomePressed(window)
    }

    function doubleRight()
    {
        if (virtualKeyboard.visible)
            virtualKeyboard.addX()
        else
            keyEmitter.keyF3Pressed(window)
    }

    function doubleLeft()
    {
        if (virtualKeyboard.visible)
            virtualKeyboard.backspace()
        else
        keyEmitter.keyF4Pressed(window)
    }

    function doubleUp()
    {
        keyEmitter.keyF5Pressed(window)
    }

    function disableShortcuts()
    {
        shortcuts.canAccept = false
    }

    function enableShortcuts()
    {
        shortcuts.canAccept = true
    }
}
