import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

Dialog {
    id: dialog

    function getFilter() {
        var matrix = []

        for (var y = 0; y < matrixGrid.rows; y++) {
            var matrixRow = []
            matrix.push(matrixRow)

            for (var x = 0; x < matrixGrid.columns; x++) {
                var field = matrixGrid.fieldAt(x, y)
                var matrixCell = parseInt(field.text)
                matrixRow.push(matrixCell)
            }
        }

        var result = {
            columns: matrixGrid.columns,
            matrix: matrix,
            anchor: anchor,
            divisor: parseInt(divisorField.text),
            offset: parseInt(offsetField.text)
        }
        result.serialize = serializeFilter.bind(null, result)
        return result
    }

    function setFilter(filter) {
        matrixGrid.setSize(filter.columns, filter.rows)
        for (var i in filter.matrix) {
            matrixGrid.children[i].text = filter.matrix[i]
        }
        setAnchor(filter.anchor)
        divisorField.text = filter.divisor
        offsetField.text = filter.offset
    }

    property variant anchor
    anchor: []

    function setAnchor(anchor) {
        dialog.anchor = anchor
        console.log("Anchor: " + anchor)
    }

    function serializeFilter(filter) {
        return "convolution:" +
            filter.columns + ":" +
            filter.matrix + ":" +
            filter.anchor + ":" +
            filter.divisor + ":" +
            filter.offset
    }

    PredefinedConvolutionFilters {
        id: predefined
    }
    
    Row {
        GridLayout {
            id: matrixGrid
            rows: 3
            columns: 3

            function fieldAt(x, y) {
                return children[y * matrixGrid.rows + x]
            }

            function setSize(columns, rows) {
                matrixGrid.rows = rows
                matrixGrid.columns = columns
            }
            
            Repeater {
                model: matrixGrid.rows * matrixGrid.columns

                TextField {
                    placeholderText: "0"
                    validator: IntValidator {}

                    style: TextFieldStyle {
                        background: Rectangle {
                            border.color: isAnchor() ? "green": "gray"
                            border.width: 1.5
                        }
                    }

                    function isAnchor() {
                        return position()[0] == anchor[0] &&
                            position()[1] == anchor[1]
                    }

                    function position() {
                        var x = index % matrixGrid.columns
                        var y = Math.floor(index / matrixGrid.rows)
                        return [x, y]
                    }
                    
                    Keys.onSpacePressed: {
                        setAnchor(position())
                    }
                }
            }
        }

        Column {
            ComboBox {
                Layout.columnSpan: 2

                Component.onCompleted: {
                    model = predefined.filters

                    dialog.setFilter(model[0].filter)
                }

                onActivated: dialog.setFilter(model[index].filter)
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

                Text {
                    text: "Size: "
                    Layout.rowSpan: 2
                }

                Text {
                    text: "x: "
                }
                TextField {
                    id: xSizeField
                    validator: IntValidator {}
                }

                Text {
                    text: "y: "
                }
                TextField {
                    id: ySizeField
                    validator: IntValidator {}
                }
            }
        }
    }
}
