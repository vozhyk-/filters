#ifndef FUNCTION_FILTER_H
#define FUNCTION_FILTER_H

#include "Filter.hpp"

class FunctionFilter : public Filter
{
public:
    FunctionFilter(int slope, int offset) : slope{slope}, offset{offset}
    {
    }

    void apply(QImage &image) const override;

private:
    int slope;
    int offset;
};

#endif // FUNCTION_FILTER_H
