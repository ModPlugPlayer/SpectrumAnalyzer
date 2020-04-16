#ifndef MATHUTIL_HPP
#define MATHUTIL_HPP
#include <QtMath>

class MathUtil
{
public:
    MathUtil();
    static void divideLineIntoSegmentsAndGaps(qreal lineSize, unsigned int segmentAmount, qreal segmentGapRatio, qreal &resultingSegmentSize, qreal &resultingGapSize);
};

#endif // MATHUTIL_HPP
