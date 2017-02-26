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
        onAccepted: loadImage(openDialog.fileUrls[0])
    }

    function loadImage(url) {
        image.source = url
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
            var filter = getFilter()

            loadImage(makeFilteredUrl(filter))
        }

        function getFilter() {
            var matrix = []

            for (var i = 0; i < matrixGrid.rows; i++) {
                var matrixRow = []
                matrix.push(matrixRow)

                for (var j = 0; j < matrixGrid.columns; j++) {
                    var field = matrixGrid.children[i * matrixGrid.rows + j]
                    var matrixCell = parseInt(field.text)
                    matrixRow.push(matrixCell)
                }
            }

            return {
                columns: matrixGrid.columns,
                matrix: matrix,
                anchor: [1, 1],
                divisor: parseInt(divisorField.text),
                offset: parseInt(offsetField.text)
            }
        }

        function setFilter(filter) {
            for (var i in filter.matrix) {
                matrixGrid.children[i].text = filter.matrix[i]
            }
            divisorField.text = filter.divisor;
            offsetField.text = filter.offset;
        }

        function makeFilteredUrl(filter) {
            return "image://filtered/" +
                serializeFilter(filter) + ";" + image.source
        }

        function serializeFilter(filter) {
            return filter.columns + ":" +
                filter.matrix + ":" +
                filter.anchor + ":" +
                filter.divisor + ":" +
                filter.offset
        }

        property variant predefinedFilters
        predefinedFilters: [
            {
                text: "Blur",
                filter: {
                    rows: 3,
                    columns: 3,
                    matrix: [1, 1, 1,
                             1, 1, 1,
                             1, 1, 1],
                    anchor: [1, 1],
                    divisor: 9,
                    offset: 0
                }
            },

            {
                text: "Sharpen",
                filter: {
                    rows: 3,
                    columns: 3,
                    matrix: [ 0, -1,  0,
                             -1,  5, -1,
                              0, -1,  0],
                    anchor: [1, 1],
                    divisor: 1,
                    offset: 0
                }
            },

            {
                text: "Mean removal",
                filter: {
                    rows: 3,
                    columns: 3,
                    matrix: [-1, -1, -1,
                             -1,  9, -1,
                             -1, -1, -1],
                    anchor: [1, 1],
                    divisor: 1,
                    offset: 0
                }
            },

            {
                text: "Horizontal edge detection",
                filter: {
                    rows: 3,
                    columns: 3,
                    matrix: [0, -1, 0,
                             0,  1, 0,
                             0,  0, 0],
                    anchor: [1, 1],
                    divisor: 1,
                    offset: 127
                }
            }
        ]

        Row {
            GridLayout {
                id: matrixGrid
                rows: 3
                columns: 3

                Repeater {
                    model: matrixGrid.rows * matrixGrid.columns

                    TextField {
                        placeholderText: "0"
                        validator: IntValidator {}

                        Keys.onSpacePressed: {
                            console.log("TODO set anchor here")
                        }
                    }
                }
            }

            Column {
                ComboBox {
                    Layout.columnSpan: 2

                    Component.onCompleted: {
                        model = filterDialog.predefinedFilters

                        filterDialog.setFilter(model[0].filter)
                    }

                    onActivated: filterDialog.setFilter(model[index].filter)
                }

                Grid {
                    columns: 2

                    Text {
                        text: "Divisor: "
                        anchors.verticalCenter: parent.center
                    }
                    TextField {
                        id: divisorField
                        placeholderText: "1"
                        validator: IntValidator {}
                    }

                    Text {
                        text: "Offset: "
                    }
                    TextField {
                        id: offsetField
                        placeholderText: "0"
                        validator: IntValidator {}
                    }
                }
            }
        }
    }
}
