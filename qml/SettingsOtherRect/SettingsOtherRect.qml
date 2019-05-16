import QtQuick 2.0

Rectangle {
    anchors.fill: parent
    visible: false

    Grid {
        anchors.centerIn: parent
        columns: 2
        spacing: 10

        CustomLabel {
            id: showPointsLabel
            labelText: qsTr("Show points?????")
        }

        CustomCheckButton {
            id: checkButton
            labelText: showPointsLabel.labelText
            height: 100
            width: 100
        }
    }

    function setActiveFocus() {
        checkButton.forceActiveFocus()
    }

    focus: true
    Keys.onEscapePressed: escapePressed()
    Keys.onBackPressed: escapePressed()

    function escapePressed() {
        visible = false
        grid.visible = true
        grid.settingsOtherButton.forceActiveFocus()
    }
}
