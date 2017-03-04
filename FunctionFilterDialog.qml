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
            (filter.argOffset || 0) + ":" +
            filter.offset
    }

    PredefinedFunctionFilters {
        id: predefined
    }

    property variant filter
    filter: predefined.filters[0]

    Column {
        anchors.fill: parent

        Repeater {
            Component.onCompleted: model = predefined.filters

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
