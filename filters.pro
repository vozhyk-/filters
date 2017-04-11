TEMPLATE = app
QT = qml quick widgets
CONFIG += c++14
SOURCES = main.cpp FilteredImageProvider.cpp ConvolutionFilter.cpp FunctionFilter.cpp MedianFilter.cpp Dither.cpp MedianCutQuantization.cpp
HEADERS = FilteredImageProvider.hpp Filter.hpp ConvolutionFilter.hpp FunctionFilter.hpp MedianFilter.hpp Dither.hpp MedianCutQuantization.hpp
