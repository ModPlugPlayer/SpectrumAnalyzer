#include "Bar.hpp"

Bar::Bar(SpectrumAnalyzerParameters &spectrumAnalyzerParameters)
{
    this->spectrumAnalyzerParameters = spectrumAnalyzerParameters;
    gradient.setStops(spectrumAnalyzerParameters.gradientStops);
}

void Bar::refreshCalculatedParameters(int width, int height)
{
    SpectrumAnalyzerParameters &p = spectrumAnalyzerParameters;
    if(spectrumAnalyzerParameters.barDirection == ORIENTATION::VERTICAL)
        calculatedParameters.peakLength = height;
    else
        calculatedParameters.peakLength = width;

    int gapAmount = p.barAmount -1;
    double totalWidth = p.barDirection==ORIENTATION::VERTICAL?width:height;
    calculatedParameters.peakLength = p.barDirection==ORIENTATION::VERTICAL?height:width;
    calculatedParameters.barWidth = (totalWidth / p.barAmount)*p.barGapRatio;
    calculatedParameters.gapWidth = (totalWidth - (calculatedParameters.barWidth*p.barAmount))/(double)gapAmount;
}

Bar::Bar() {

}

void Bar::setValue(double value) {
    this->value = value;
    this->length = calculatedParameters.peakLength * value / spectrumAnalyzerParameters.peakValue;
}

double Bar::getValue(){
    return this->value;
}
double Bar::getLength(){
    return this->length;
}
