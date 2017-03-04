#ifndef FILTER_H
#define FILTER_H

#include <QImage>

class Filter
{
public:
    virtual void apply(QImage &image) const = 0;

    static int clamp(int value)
    {
        if (value > 255)
            return 255;
        else if (value < 0)
            return 0;
        else
            return value;
    }
};

#endif // FILTER_H
