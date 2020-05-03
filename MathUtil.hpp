#ifndef MATHUTIL_HPP
#define MATHUTIL_HPP
#include <QtMath>

class MathUtil
{
public:
    template<class T> static inline void divideLineIntoSegmentsAndGaps(T lineSize, unsigned int segmentAmount, T segmentGapRatio, T &resultingSegmentSize, T &resultingGapSize);
    template<class T> static inline T clamp(T x, T a, T b);
};

template <class T> inline T MathUtil::clamp(T x, T a, T b){    return x < a ? a : (x > b ? b : x);}

template <class T> inline void MathUtil::divideLineIntoSegmentsAndGaps(T lineSize, unsigned int segmentAmount, T segmentGapRatio, T &resultingSegmentSize, T &resultingGapSize){
    T totalPartsSize = lineSize * segmentGapRatio;
    T totalGapsSize = lineSize - totalPartsSize;

    resultingSegmentSize = totalPartsSize / segmentAmount;
    resultingGapSize = totalGapsSize / (segmentAmount - 1);
}

#endif // MATHUTIL_HPP
