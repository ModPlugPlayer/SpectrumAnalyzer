#include "ContinuousBar.hpp"
#include <QPainter>
ContinuousBar::ContinuousBar(SpectrumAnalyzerParameters &spectrumAnalyzerParameters):Bar(spectrumAnalyzerParameters) {

}

void ContinuousBar::draw(QPainter &painter) {
    SpectrumAnalyzerParameters &p = spectrumAnalyzerParameters;


    if(p.barDirection == ORIENTATION::VERTICAL)
        painter.fillRect(QRectF(coordinates.x(), coordinates.y(), calculatedParameters.barWidth, length), gradient);
//    else
  //      painter.fillRect(QRectF(0, (barWidth + gapWidth)*i, currentBarHeight, barWidth), gradient);

}

