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

Dialog {
    id: dialog

    function getFilter() {
        return filter
    }

    property RandomDither filter: RandomDither {
        levels: parseInt(levelsField.text) || defaultFilter.levels
        threshold: parseFloat(thresholdField.text) || defaultFilter.threshold
    }

    property RandomDither defaultFilter: RandomDither {
        levels: 2
        threshold: 0.9
    }

    Grid {
        columns: 2

        Text {
            text: "Number of grey levels: "
        }
        TextField {
            id: levelsField
            placeholderText: defaultFilter.levels
            validator: IntValidator {
                // TODO powers of 2
            }
        }

        Text {
            text: "Threshold: "
        }
        TextField {
            id: thresholdField
            placeholderText: defaultFilter.threshold
            validator: DoubleValidator {
                // TODO 0 to 1
            }
        }
    }
}
