import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.2

Rectangle {
    id: audioSettingRect

    property int definedHeight: 50

    visible: false
    anchors.fill: parent

    Flickable {
        id: flickable
        anchors.fill: parent
        contentHeight: 11 * 60

        Grid {
            anchors.fill: parent
            columns: 2
            spacing: 10

            CustomLabel {
                id: durationLabel
                labelText: qsTr("Duration")
            }

            CustomSliderRect {
                id: durationSlider
                width: graphSettingRect.width - durationLabel.width - 10
                text: durationLabel.labelText
                minValue: 10
                maxValue: 120
                sliderValue: myparameters.duration
                onSliderValueChanged: myparameters.duration = sliderValue
            }

            CustomLabel {
                id: minFreqLabel
                labelText: qsTr("Minimum\nfrequency")
            }

            CustomSliderRect {
                id: minFreqSlider
                width: graphSettingRect.width - durationLabel.width - 10
                text: minFreqLabel.labelText
                minValue: 200
                maxValue: 8000
                step: 100
                sliderValue: myparameters.minFreq
                onSliderValueChanged: myparameters.minFreq = sliderValue
            }

            CustomLabel {
                id: maxFreqLabel
                labelText: qsTr("Maximum\nfrequency")
            }

            CustomSliderRect {
                id: maxFreqSlider
                width: graphSettingRect.width - durationLabel.width - 10
                text: maxFreqLabel.labelText
                minValue: 200
                maxValue: 8000
                step: 100
                sliderValue: myparameters.maxFreq
                onSliderValueChanged: myparameters.maxFreq = sliderValue
            }

            CustomLabel {
                id: resetLabel
                labelText: ""
            }

            CustomButton {
                id: restoreButton
                width: audioSettingsRect.width - durationLabel.width - 10
                height: 50//definedHeight
                textSize: width / 50 + 10
                showText: qsTr("Restore defaults")
                customText: showText
                onPressed: {
                    myparameters.resetAudio()
                    durationSlider.sliderValue = myparameters.duration
                    minFreqSlider.sliderValue = myparameters.minFreq
                    maxFreqSlider.sliderValue = myparameters.maxFreq
                }
            }
        }
    }

    function setActiveFocus() {
        //flickable.contentY = 0
        durationSlider.setFocus()
    }

    focus: true
    Keys.onEscapePressed: escapePressed()
    Keys.onBackPressed: escapePressed()

    function escapePressed() {
        audioSettingsRect.visible = false
        grid.visible = true
        grid.audioSettingsButton.forceActiveFocus()
    }
}

