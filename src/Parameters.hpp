#ifndef PARAMETERS_HPP
#define PARAMETERS_HPP
#include <QGradientStops>

struct DiscreteParameters {
    int barLedAmount;
    double ledGapRatio;
};

enum MovementType {
	Instant,
	ConstantVelocity,
	ConstantAcceleration
};

template <class T>
struct MovementParameters{
	MovementType movementType = MovementType::Instant;
	T acceleration = T(0);
	T initialVelocity = T(0);
};

template<class T>
struct SpectrumAnalyzerParameters{
    Qt::Orientation barDirection;
    unsigned char dimmingPercentage = 0;
    unsigned char transparencyPercentage = 100;
    double blackCoefficient;
    int barAmount;
	T peakValue;
	T floorValue;
    double barGapRatio;

	double instantPeakValueIndicatorTimeout = 0; //Peak value indicator timeout in miliseconds. 0 for disabling the indicator
	MovementParameters<T> raisingMovement;
	MovementParameters<T> fallingMovement;

	DiscreteParameters discreteParameters;
    QGradientStops gradientStops;
};

#endif // PARAMETERS_HPP
