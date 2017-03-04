#ifndef CONVOLUTION_FILTER_HPP
#define CONVOLUTION_FILTER_HPP

#include <QVector>
#include <QImage>

class ConvolutionFilter
{
public:
    using matrixT = QVector<int>;

    ConvolutionFilter(int columns, matrixT matrix,
                      QPoint anchor, int divisor, int offset) :
        columns{columns}, matrix{matrix}, anchor{anchor},
        divisor{divisor}, offset{offset}
    {
    }

    void apply(QImage &image);

private:
    int columns;
    matrixT matrix;
    QPoint anchor;
    int divisor;
    int offset;

    QSize size() {
        return QSize{columns, matrix.length() / columns};
    }

    int get(int x, int y) { return matrix[y * columns + x]; }

    void applyAtPoint(
        const QImage &original, QImage &image, const QPoint &toProcess);
    QRgb colorAtPoint(const QImage &original, const QPoint &point);
};

#endif // CONVOLUTION_FILTER_HPP
