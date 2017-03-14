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

import QtQml 2.2

QtObject {
    property variant filters
    filters: [
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
            text: "9x9 Blur",
            filter: {
                rows: 9,
                columns: 9,
                matrix: [1, 1, 1, 1, 1, 1, 1, 1, 1,
                         1, 1, 1, 1, 1, 1, 1, 1, 1,
                         1, 1, 1, 1, 1, 1, 1, 1, 1,
                         1, 1, 1, 1, 1, 1, 1, 1, 1,
                         1, 1, 1, 1, 1, 1, 1, 1, 1,
                         1, 1, 1, 1, 1, 1, 1, 1, 1,
                         1, 1, 1, 1, 1, 1, 1, 1, 1,
                         1, 1, 1, 1, 1, 1, 1, 1, 1,
                         1, 1, 1, 1, 1, 1, 1, 1, 1],
                anchor: [4, 4],
                divisor: 81,
                offset: 0
            }
        },

        {
            text: "Gaussian Blur",
            filter: {
                rows: 3,
                columns: 3,
                matrix: [0, 1, 0,
                         1, 4, 1,
                         0, 1, 0],
                anchor: [1, 1],
                divisor: 8,
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
        },

        {
            text: "East emboss",
            filter: {
                rows: 3,
                columns: 3,
                matrix: [-1, 0, 1,
                         -1, 1, 1,
                         -1, 0, 1],
                anchor: [1, 1],
                divisor: 1,
                offset: 0
            }
        },

        {
            text: "Left shift",
            filter: {
                rows: 3,
                columns: 3,
                matrix: [0, 0, 0,
                         0, 1, 0,
                         0, 0, 0],
                anchor: [0, 1],
                divisor: 1,
                offset: 0
            }
        }
    ]
}