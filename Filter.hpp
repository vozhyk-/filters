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
};

#endif // FILTER_HPP
