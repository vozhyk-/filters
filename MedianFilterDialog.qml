import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

Dialog {
    id: dialog

    function getFilter() {
        return {
            serialize: serializeFilter
        }
    }

    function serializeFilter() {
        return "median:"
    }
}
