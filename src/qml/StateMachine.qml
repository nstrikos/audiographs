import QtQuick 2.12
//import QtQuick.Window 2.12

//import QtQml.StateMachine 1.0 as DSM

Item {

}

//Item {
//    DSM.StateMachine {
//        id: stateMachine
//        initialState: initialState
//        running: true
//        DSM.State {
//            id: initialState
//            DSM.SignalTransition {
//                targetState: evaluateState
//                signal: window.evaluate
//            }
////            DSM.SignalTransition {
////                targetState: errorDisplayState
////                signal: window.playPressed
////            }
//            onEntered: {
//                console.log("initial state")
//                qmlConnector.setDerivativeMode(0)
//                window.graphRect.pointView.clear()
//                window.graphRect.derivativeView.setUpdate(false);
//                window.graphRect.graphCanvas.updateCanvas(-10, 10, -10, 10)
//                disableControls()
//            }
//        }

//        DSM.State {
//            id: errorDisplayState
//            DSM.SignalTransition {
//                targetState: initialState
//                signal: window.errorAccepted
//            }
//            onEntered: {
//                console.log("error state")
//                //window.showError(functionExpression.getError())
//            }
//        }

//        DSM.State {
//            id: evaluateState
//            DSM.SignalTransition {
//                targetState: initialState
//                signal: error
//            }
//            DSM.SignalTransition {
//                targetState: graphReadyState
//                signal: newGraph
//            }
//            onEntered: {
//                console.log("evaluate state")
//                disableControls()
//                qmlConnector.setDerivativeMode(0)
//                window.graphRect.derivativeView.setUpdate(false);
//                window.graphRect.derivativeView.visible = false
//                qmlConnector.calculate(controlsRect.textInput.text,
//                                             controlsRect.textInput2.text,
//                                             controlsRect.textInput3.text,
//                                             controlsRect.textInput4.text,
//                                             controlsRect.textInput5.text)
//            }
//        }

//        DSM.State {
//            id: graphReadyState
//            DSM.SignalTransition {
//                targetState: evaluateState
//                signal: window.evaluate
//            }
//            DSM.SignalTransition {
//                targetState: initialState
//                signal: error
//            }
//            DSM.SignalTransition {
//                targetState: graphReadyState
//                signal: newGraph
//            }
//            DSM.SignalTransition {
//                targetState: playSoundState
//                signal: playPressed
//            }
//            DSM.SignalTransition {
//                targetState: exploreState
//                signal: explore
//            }
//            DSM.SignalTransition {
//                targetState: interestingPointState
//                signal: interestingPoint
//            }
//            onEntered: {
//                console.log("graph ready state")
//                enableControls()
//                controlsRect.startSoundButton.text = qsTr("Start sound")
//                graphRect.updateCanvas()
//                window.graphRect.pointView.clear()
//            }
//        }

//        DSM.State {
//            id: playSoundState

//            DSM.SignalTransition {
//                targetState: evaluateState
//                signal: window.evaluate
//            }

//            DSM.SignalTransition {
//                targetState: graphReadyState
//                signal: stopAudio
//            }
//            DSM.SignalTransition {
//                targetState: graphReadyState
//                signal: newGraph
//            }
//            DSM.SignalTransition {
//                targetState: graphReadyState
//                signal: playPressed
//            }
//            DSM.SignalTransition {
//                targetState: exploreState
//                signal: explore
//            }
//            DSM.SignalTransition {
//                targetState: interestingPointState
//                signal: interestingPoint
//            }
//            onEntered: {
//                console.log("play sound state")
//                enableControls()
//                controlsRect.startSoundButton.text = qsTr("Stop sound")
//                qmlConnector.playSound()
//            }
//            onExited: {
//                controlsRect.startSoundButton.text = qsTr("Start sound")
//                qmlConnector.stopSound()
//                //window.graphRect.pointView.clear()
//            }
//        }

//        DSM.State {
//            id: exploreState
//            DSM.SignalTransition {
//                targetState: evaluateState
//                signal: evaluate
//            }

//            DSM.SignalTransition {
//                targetState: playSoundState
//                signal: playPressed
//            }
//            DSM.SignalTransition {
//                targetState: graphReadyState
//                signal: newGraph
//            }
//            DSM.SignalTransition {
//                targetState: interestingPointState
//                signal: interestingPoint
//            }
//            onEntered: {
//                console.log("explore state")
//                //functionController.stopAudio()
//                functionExpression.stopAudio()
//            }
//        }
//        DSM.State {
//            id: interestingPointState
//            DSM.SignalTransition {
//                targetState: evaluateState
//                signal: evaluate
//            }

//            DSM.SignalTransition {
//                targetState: exploreState
//                signal: playPressed
//            }
//            DSM.SignalTransition {
//                targetState: graphReadyState
//                signal: newGraph
//            }
//            DSM.SignalTransition {
//                targetState: exploreState
//                signal: explore
//            }
//            DSM.SignalTransition {
//                targetState: interestingPointStoppedState
//                signal: interestingPointFinished
//            }
//            onEntered: {
//                console.log("interesting point state")
//                controlsRect.startSoundButton.text = qsTr("Stop sound")
//            }
//            onExited: {
//                controlsRect.startSoundButton.text = qsTr("Start sound")
//                functionExpression.stopAudio()
//            }
//        }

//        DSM.State {
//            id: interestingPointStoppedState
//            DSM.SignalTransition {
//                targetState: evaluateState
//                signal: evaluate
//            }

//            DSM.SignalTransition {
//                targetState: exploreState
//                signal: playPressed
//            }
//            DSM.SignalTransition {
//                targetState: graphReadyState
//                signal: newGraph
//            }
//            DSM.SignalTransition {
//                targetState: exploreState
//                signal: explore
//            }
//            DSM.SignalTransition {
//                targetState: interestingPointState
//                signal: interestingPoint
//            }
//            onEntered: {
//                console.log("interesting point finished")
//                controlsRect.startSoundButton.text = qsTr("Start sound")
//            }
//        }

//    }

//    function disableControls()
//    {
//        controlsRect.startSoundButton.enabled = false
//        window.canZoomDrag = false
//    }

//    function enableControls()
//    {
//        controlsRect.startSoundButton.enabled = true
//        window.canZoomDrag = true
//    }
//}
