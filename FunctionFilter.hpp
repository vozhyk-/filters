#ifndef FUNCTION_FILTER_H
#define FUNCTION_FILTER_H

#include "Filter.hpp"

class FunctionFilter : public Filter
{
public:
    FunctionFilter(double slope, int offset) : slope{slope}, offset{offset}
    {
    }

    void apply(QImage &image) const override;

private:
    double slope;
    int offset;

    void applyAtPoint(QImage &image, const QPoint &toProcess) const;
    QRgb colorAtPoint(QImage &image, const QPoint &point) const;
    unsigned char colorForChannel(unsigned char channel) const;
};

#endif // FUNCTION_FILTER_H
