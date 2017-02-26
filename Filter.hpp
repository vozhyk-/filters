#ifndef FILTER_HPP
#define FILTER_HPP

#include <QVector>
#include <QImage>

class Filter
{
public:
    Filter(int columns, QVector<double> matrix) :
        columns{columns}, matrix{matrix}
    {
    }

    void apply(QImage &image);

private:
    int columns;
    QVector<double> matrix{};
};

#endif // FILTER_HPP
