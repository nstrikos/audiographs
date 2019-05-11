import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

Rectangle {
    id: root

    property alias input3: input3
    property alias input4: input4
    property alias checkboxDrawLine: checkboxDrawLine

    property int spacing: 5


    color: "white"
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    anchors.left: buttonsRect.right
    anchors.right: parent.right
    visible: true
    Column {
        spacing: spacing
        anchors.fill: parent
        TextEditLayout {
            id: input3
            labelText: qsTr("Sound\npreferences")
            input.text: "Default"
            KeyNavigation.tab: input4
        }
        TextEditLayout {
            id: input4
            labelText: qsTr("Frequence:")
            input.text: "10"
            KeyNavigation.tab: checkboxDrawLine
        }

        CheckBox {
            id: checkboxDrawLine
            height: 20
            text: "Low"
            checked: false
            KeyNavigation.tab: buttonsRect.parametersButton
            //width: parent.width
            onCheckedChanged: canvas.drawLinesEnabled = checked
        }
    }
}
