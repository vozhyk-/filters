import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

Dialog {
    id: dialog

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

        var result = {
            columns: matrixGrid.columns,
            matrix: matrix,
            anchor: [1, 1],
            divisor: parseInt(divisorField.text),
            offset: parseInt(offsetField.text)
        }
        result.serialize = serializeFilter.bind(null, result)
        return result
    }

    function setFilter(filter) {
        for (var i in filter.matrix) {
            matrixGrid.children[i].text = filter.matrix[i]
        }
        divisorField.text = filter.divisor;
        offsetField.text = filter.offset;
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
            }
        }
    }
}
