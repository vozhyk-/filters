#ifndef MEDIAN_FILTER_HPP
#define MEDIAN_FILTER_HPP

#include "Filter.hpp"

class MedianFilter : public Filter
{
public:
    MedianFilter()
    {
    }

    void apply(QImage &image) const override;

private:
    QPoint anchor{1, 1};

    QSize size() const {
        return QSize{3, 3};
    }

    void applyAtPoint(
        const QImage &original, QImage &image, const QPoint &toProcess) const;
    QRgb colorAtPoint(const QImage &original, const QPoint &point) const;
};


#endif // MEDIAN_FILTER_HPP
