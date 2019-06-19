import QtQuick 2.0
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Styles.Flat 1.0 as Flat
import QtQuick.Layouts 1.12


import "qml/GraphRect"
import "qml/MainGrid"

Rectangle {
    width: parent.height
    height: 8 * Flat.FlatStyle.scaleFactor
    rotation: 90
    anchors.left: parent.right
    transformOrigin: Item.TopLeft

    gradient: Gradient {
        GradientStop {
            color: Qt.rgba(0, 0, 0, 0.15)
            position: 0
        }
        GradientStop {
            color: Qt.rgba(0, 0, 0, 0.05)
            position: 0.5
        }
        GradientStop {
            color: Qt.rgba(0, 0, 0, 0)
            position: 1
        }
    }
}
