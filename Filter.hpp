#ifndef FILTER_H
#define FILTER_H

#include <QImage>

class Filter
{
public:
    virtual void apply(QImage &image) const = 0;
};

#endif // FILTER_H
