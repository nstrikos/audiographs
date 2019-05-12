import QtQuick 2.9
import QtQuick.Controls 1.4
import QtQml 2.2

TableView {
    id: tableView
    anchors {
        top: parent.top
        bottom: parent.bottom
        left: buttonsSelection.right
        right: parent.right
    }
    visible: false
    TableViewColumn {
        role: "title"
        title: "Title"
        width: 100
    }
    TableViewColumn {
        role: "author"
        title: "Author"
        width: 200
    }
    model: libraryModel
    ListModel {
        id: libraryModel
        ListElement {
            title: "A Masterpiece"
            author: "Gabriel"
        }
        ListElement {
            title: "Brilliance"
            author: "Jens"
        }
        ListElement {
            title: "Outstanding"
            author: "Frederik"
        }
    }
}
