import QtQuick 2.0
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Styles.Flat 1.0 as Flat
import QtQuick.Layouts 1.12


Rectangle {
//    width: parent.height
//    height: 8 * Flat.FlatStyle.scaleFactor
//    rotation: 90
//    anchors.left: parent.right
//    transformOrigin: Item.TopLeft

    width: parent.width
    height: 8
    anchors.left: parent.left
    anchors.bottom: parent.bottom
//    y: -100
    z: 1010101
    visible: (controlsRect.height > 0) && (!anchorToLeft)


    color: "blue"

    gradient: Gradient {
        GradientStop {
            color: Qt.rgba(0, 0, 0, 0.4)
            position: 1
        }
        GradientStop {
            color: Qt.rgba(0, 0, 0, 0.15)
            position: 0.5
        }
        GradientStop {
            color: Qt.rgba(0, 0, 0, 0)
            position: 0
        }
    }
}
