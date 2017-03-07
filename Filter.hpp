#ifndef FILTER_H
#define FILTER_H

#include <QImage>

class Filter
{
public:
    virtual void apply(QImage &image) const = 0;

    static int clamp(int channel)
    {
        return clamp(channel, 0, 256);
    }

    //! clamp inside the [start, end) range:
    //! if value == end, return end - 1
    static int clamp(int value, int start, int end)
    {
        if (value >= end)
            return end - 1;
        else if (value < start)
            return start;
        else
            return value;
    }
};

#endif // FILTER_H
