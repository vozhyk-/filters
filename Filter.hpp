#ifndef FILTER_HPP
#define FILTER_HPP

#include <QVector>
#include <QImage>

class Filter
{
public:
    using matrixT = QVector<int>;

    Filter(int columns, matrixT matrix, int divisor) :
        columns{columns}, matrix{matrix}, divisor{divisor}
    {
    }

    void apply(QImage &image);

private:
    int columns;
    matrixT matrix;
    int divisor;

    QSize size() {
        return QSize{columns, matrix.length() / columns};
    }

    int get(int x, int y) { return matrix[y * columns + x]; }

    void applyAtPoint(
        const QImage &original, QImage &image, const QPoint &toProcess);
    QRgb colorAtPoint(const QImage &original, const QPoint &point);
};

#endif // FILTER_HPP
