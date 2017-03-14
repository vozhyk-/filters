/*
 * Copyright (c) 2017 Witaut Bajaryn
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

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
            MenuItem { action: applyFunctionFilterAction }
            MenuItem { action: applyMedianFilterAction }
            MenuItem { action: applyRandomDitheringAction }
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
        id: applyMedianFilterAction
        text: "Apply &Median Filter..."
        shortcut: "Alt+Return"
        onTriggered: medianFilterDialog.visible = true
    }

    Action {
        id: applyFunctionFilterAction
        text: "Apply &Function Filter..."
        shortcut: "Shift+Return"
        onTriggered: functionFilterDialog.visible = true
    }

    Action {
        id: applyRandomDitheringAction
        text: "Apply &Random Dithering..."
        shortcut: "D"
        onTriggered: randomDitherDialog.visible = true
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

    MedianFilterDialog {
        id: medianFilterDialog

        onAccepted: addFilter(getFilter())
    }

    FunctionFilterDialog {
        id: functionFilterDialog

        onAccepted: addFilter(getFilter())
    }

    RandomDitherDialog {
        id: randomDitherDialog

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
            serializedFilters.push(filters[i].serialize())
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
