#include "MathUtil.hpp"

MathUtil::MathUtil()
{

}

void MathUtil::divideLineIntoSegmentsAndGaps(qreal lineSize, unsigned int segmentAmount, qreal segmentGapRatio, qreal &resultingSegmentSize, qreal &resultingGapSize)
{
    qreal partSize = lineSize/segmentAmount; // partSize = segmentSize + gapSize
    resultingSegmentSize = partSize*segmentGapRatio;
    resultingGapSize = partSize - resultingSegmentSize;
}
