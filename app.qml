import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

ApplicationWindow {
    visible: true
    title: "Convolution Filters"

    menuBar: MenuBar {
        Menu {
            title: "&File"
            MenuItem { action: openAction }
        }

        Menu {
            title: "&Edit"
            MenuItem { action: applyFilterAction }
        }
    }

    Image {
        id: image
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
    }

    FileDialog {
        id: openDialog
        folder: shortcuts.home
        onAccepted: image.source = openDialog.fileUrls[0]
    }

    Action {
        id: openAction
        text: "&Open..."
        shortcut: StandardKey.Open
        iconName: "file-open"
        onTriggered: openDialog.visible = true
    }

    Action {
        id: applyFilterAction
        text: "Apply &Filter..."
        shortcut: "Return"
        onTriggered: filterDialog.visible = true
    }

    Dialog {
        id: filterDialog
        onAccepted: {
            var filter = parseFilter(filterGrid)

            console.log("Filter: " + filter)
            image.source = ""
        }

        function parseFilter(grid) {
            var filter = []

            for (var i = 0; i < filterGrid.rows; i++) {
                var filterRow = []
                filter.push(filterRow)

                for (var j = 0; j < filterGrid.columns; j++) {
                    var field = filterGrid.children[i * filterGrid.rows + j]
                    var filterCell = field.text
                    filterRow.push(filterCell)
                }
            }

            return filter
        }

        GridLayout {
            id: filterGrid
            rows: 3
            columns: 3

            Repeater {
                model: filterGrid.rows * filterGrid.columns

                TextField {
                    placeholderText: "0"
                    validator: RegExpValidator {
                        regExp: /\d+(\.\d+)?/
                    }
                }
            }
        }
    }
}
