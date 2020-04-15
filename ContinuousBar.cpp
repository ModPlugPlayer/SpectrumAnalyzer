#include "ContinuousBar.hpp"
#include <QPainter>
ContinuousBar::ContinuousBar(SpectrumAnalyzer *spectrumAnalyzer):Bar(spectrumAnalyzer) {
    this->spectrumAnalyzer = spectrumAnalyzer;
}

void ContinuousBar::draw(QPainter &painter) {
    SpectrumAnalyzerParameters &p = spectrumAnalyzer->parameters;


    if(p.barDirection == ORIENTATION::VERTICAL)
        painter.fillRect(QRectF(getCoordinates().x(), getCoordinates().y(), spectrumAnalyzer->calculatedParameters.barWidth, length), gradient);
//    else
  //      painter.fillRect(QRectF(0, (barWidth + gapWidth)*i, currentBarHeight, barWidth), gradient);

}
