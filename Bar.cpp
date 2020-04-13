#include "Bar.hpp"

Bar::Bar(SpectrumAnalyzer *spectrumAnalyzer)
{
    this->spectrumAnalyzer = spectrumAnalyzer;
}


Bar::Bar() {

}

void Bar::setValue(double value) {
    this->value = value;
    this->length = spectrumAnalyzer->calculatedParameters.peakLength * value / spectrumAnalyzer->parameters.peakValue;
}

double Bar::getValue(){
    return this->value;
}
double Bar::getLength(){
    return this->length;
}
