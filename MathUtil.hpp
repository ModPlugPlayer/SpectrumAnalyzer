#ifndef MATHUTIL_HPP
#define MATHUTIL_HPP
#include <QtMath>

class MathUtil
{
public:
    template<class T> static inline void divideLineIntoSegmentsAndGaps(T lineSize, unsigned int segmentAmount, T segmentGapRatio, T &resultingSegmentSize, T &resultingGapSize);
    template<class T> static inline T clamp(T x, T a, T b);
    template<class T> static inline T elementAmount(T firstElement, T lastElement, T commonDifference);
    template<class T> static inline T findNthElementByIndex(T firstElement, T commonDifference, size_t n);
    template<class T> static inline T findNthElemen(T firstElement, T commonDifference, size_t n);

};

template <class T> inline T MathUtil::clamp(T x, T a, T b) {
    return x < a ? a : (x > b ? b : x);
}

template <class T> inline void MathUtil::divideLineIntoSegmentsAndGaps(T lineSize, unsigned int segmentAmount, T segmentGapRatio, T &resultingSegmentSize, T &resultingGapSize) {
    T totalPartsSize = lineSize * segmentGapRatio;
    T totalGapsSize = lineSize - totalPartsSize;

    resultingSegmentSize = totalPartsSize / segmentAmount;
    resultingGapSize = totalGapsSize / (segmentAmount - 1);
}

template<class T> inline T elementAmount(T firstElement, T lastElement, T commonDifference) {
    return ((lastElement-firstElement)/commonDifference) +1;
}

template<class T> static inline T findNthElementByIndex(T firstElement, T commonDifference, size_t n) {
    return  firstElement + n*commonDifference;
}

//n starts from 1
template<class T> static inline T findNthElemen(T firstElement, T commonDifference, size_t n) {
    return  firstElement + commonDifference*(n-1);
}

#endif // MATHUTIL_HPP
