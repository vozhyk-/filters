import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

ApplicationWindow {
    visible: true
    title: "Filters"

    menuBar: MenuBar {
        Menu {
            title: "&File"
            MenuItem { action: openAction }
        }

        Menu {
            title: "&Edit"
            MenuItem { action: applyConvolutionFilterAction }
            MenuItem { action: undoAction }
            MenuItem { action: redoAction }
        }
    }

    Action {
        id: openAction
        text: "&Open..."
        shortcut: StandardKey.Open
        iconName: "file-open"
        onTriggered: openDialog.visible = true
    }

    Action {
        id: applyConvolutionFilterAction
        text: "Apply &Convolution Filter..."
        shortcut: "Return"
        onTriggered: convolutionFilterDialog.visible = true
    }

    Action {
        id: undoAction
        text: "&Undo"
        shortcut: StandardKey.Undo
        onTriggered: undoFilter()
    }

    Action {
        id: redoAction
        text: "&Redo"
        shortcut: StandardKey.Redo
        onTriggered: redoFilter()
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

    ConvolutionFilterDialog {
        id: convolutionFilterDialog

        onAccepted: addFilter(getFilter())
    }

    property url originalImageUrl

    property variant filters
    filters: []

    property variant undoneFilters
    undoneFilters: []

    function addFilter(filter) {
        filters.push(filter);
        loadFilteredImage()
    }

    function undoFilter() {
        moveFilter(filters, undoneFilters)
    }

    function redoFilter() {
        moveFilter(undoneFilters, filters)
    }

    function moveFilter(source, destination) {
        var filter = source.pop()
        if (filter === undefined)
            return;

        destination.push(filter)
        loadFilteredImage()
    }

    function loadFilteredImage() {
        loadImage(makeFilteredUrl())
    }

    function makeFilteredUrl() {
        if (filters.length === 0)
            return originalImageUrl;

        var serializedFilters = []
        for (var i in filters) {
            serializedFilters.push(
                convolutionFilterDialog.serializeFilter(
                    filters[i]))
        }
        var serializedFilterList = serializedFilters.join("/")

        return "image://filtered/" + serializedFilterList + ";" + originalImageUrl
    }

    function loadNewImage(url) {
        loadImage(originalImageUrl = url)
        filters = []
        undoneFilters = []
    }

    function loadImage(url) {
        console.log(url)
        image.source = url
    }
}
