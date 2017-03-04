#ifndef CONVOLUTION_FILTER_HPP
#define CONVOLUTION_FILTER_HPP

#include "Filter.hpp"

#include <QVector>

class ConvolutionFilter : public Filter
{
public:
    using matrixT = QVector<int>;

    ConvolutionFilter(int columns, matrixT matrix,
                      QPoint anchor, int divisor, int offset) :
        columns{columns}, matrix{matrix}, anchor{anchor},
        divisor{divisor}, offset{offset}
    {
    }

    void apply(QImage &image) const override;

private:
    int columns;
    matrixT matrix;
    QPoint anchor;
    int divisor;
    int offset;

    QSize size() const {
        return QSize{columns, matrix.length() / columns};
    }

    int get(int x, int y) const { return matrix[y * columns + x]; }

    void applyAtPoint(
        const QImage &original, QImage &image, const QPoint &toProcess) const;
    QRgb colorAtPoint(const QImage &original, const QPoint &point) const;
};

#endif // CONVOLUTION_FILTER_HPP
