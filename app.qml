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
        onAccepted: loadNewImage(openDialog.fileUrls[0])
    }

    FilterDialog {
        id: filterDialog

        onAccepted: {
            addFilter(getFilter())
            loadFilteredImage()
        }
    }

    property url originalImageUrl
    originalImageUrl: ""

    property variant filters
    filters: []

    function addFilter(filter) {
        filters.push(filter);
    }

    function loadFilteredImage() {
        loadImage(makeFilteredUrl())
    }

    function makeFilteredUrl() {
        var serializedFilters = []
        for (var i in filters) {
            serializedFilters.push(filterDialog.serializeFilter(filters[i]))
        }
        var serializedFilterList = serializedFilters.join("/")

        return "image://filtered/" + serializedFilterList + ";" + originalImageUrl
    }

    function loadNewImage(url) {
        loadImage(originalImageUrl = url)
    }

    function loadImage(url) {
        console.log(url)
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
}
