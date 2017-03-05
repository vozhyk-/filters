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
                anchor: [1, 1],
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