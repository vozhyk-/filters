import QtQml 2.2

QtObject {
    property variant filters
    filters: [
        {
            text: "Contrast +",
            filter: {
                slope: 1.3,
                argOffset: -127,
                offset: 127
            }
        },
        {
            text: "Contrast -",
            filter: {
                slope: 0.7,
                argOffset: -127,
                offset: 127
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
}
