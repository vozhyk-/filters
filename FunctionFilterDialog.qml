import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

Dialog {
    id: dialog

    function getFilter() {
        var result = filter
        result.serialize = serializeFilter.bind(null, result)
        return result
    }

    function serializeFilter(filter) {
        return "function:" +
            filter.slope + ":" +
            filter.offset
    }

    property variant predefinedFilters
    predefinedFilters: [
        {
            text: "Contrast +",
            filter: {
                slope: 1.3,
                offset: 0
            }
        },
        {
            text: "Contrast -",
            filter: {
                slope: 0.7,
                offset: 0
            }
        },

        {
            text: "Brightness +",
            filter: {
                slope: 1,
                offset: 20
            }
        },
        {
            text: "Brightness -",
            filter: {
                slope: 1,
                offset: -20
            }
        },

        {
            text: "Negation",
            filter: {
                slope: -1,
                offset: 255
            }
        }
    ]

    property variant filter
    filter: predefinedFilters[0]

    Column {
        anchors.fill: parent

        Repeater {
            Component.onCompleted: model = dialog.predefinedFilters

            delegate: Button {
                text: modelData.text

                onClicked: {
                    filter = modelData.filter
                    accept()
                }
            }
        }
    }
}
