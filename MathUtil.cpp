#include "MathUtil.hpp"

MathUtil::MathUtil()
{

}

void MathUtil::divideLineIntoSegmentsAndGaps(qreal lineSize, unsigned int segmentAmount, qreal segmentGapRatio, qreal &resultingSegmentSize, qreal &resultingGapSize)
{
    qreal totalPartsSize = lineSize * segmentGapRatio;
    qreal totalGapsSize = lineSize - totalPartsSize;

    resultingSegmentSize = totalPartsSize / segmentAmount;
    resultingGapSize = totalGapsSize / (segmentAmount - 1);
}
