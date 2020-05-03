#ifndef MATHUTIL_HPP
#define MATHUTIL_HPP
#include <cmath>

namespace MathUtil
{
    template<class T> inline void divideLineIntoSegmentsAndGaps(T lineSize, unsigned int segmentAmount, T segmentGapRatio, T &resultingSegmentSize, T &resultingGapSize);
    template<class T> inline T clamp(T x, T a, T b);
    namespace ArithmeticProgression{
        template<class T> inline T elementAmount(T firstElement, T lastElement, T commonDifference);
        template<class T> inline T findNthElementByIndex(T firstElement, T commonDifference, size_t n);
        template<class T> inline T findNthElement(T firstElement, T commonDifference, size_t n);
        template<class T> inline T sumFirstNElementsByCommonDifference(T firstElement, T commonDifference, size_t n);
        template<class T> inline T sumFirstNElementsByLastElement(T firstElement, T lastElement, size_t n);
    }
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

template<class T> inline T MathUtil::ArithmeticProgression::elementAmount(T firstElement, T lastElement, T commonDifference) {
    return ((lastElement-firstElement)/commonDifference) +1;
}

template<class T> inline T MathUtil::ArithmeticProgression::findNthElementByIndex(T firstElement, T commonDifference, size_t n) {
    return  firstElement + n*commonDifference;
}

//n starts from 1
template<class T> inline T MathUtil::ArithmeticProgression::findNthElement(T firstElement, T commonDifference, size_t n) {
    return  firstElement + commonDifference*(n-1);
}

template<class T> inline T MathUtil::ArithmeticProgression::sumFirstNElementsByCommonDifference(T firstElement, T commonDifference, size_t n) {
    return (firstElement*2 + commonDifference*(n-1))/2;
}

template<class T> inline T MathUtil::ArithmeticProgression::sumFirstNElementsByLastElement(T firstElement, T lastElement, size_t n) {
    return (firstElement + lastElement)*n/2;
}

#endif // MATHUTIL_HPP
