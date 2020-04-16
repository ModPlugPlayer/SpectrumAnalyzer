#ifndef BAR_HPP
#define BAR_HPP
#include <QWidget>
#include "Enums.hpp"
#include "Drawable.hpp"
#include "Dimmable.hpp"

class Bar : public Drawable, public Dimmable
{
public:
    Bar();
    virtual void draw(QPainter &painter) = 0;

    double getValue();
    void setValue(const double &value);

    double getPeakValue();
    void setPeakValue(const double &peakValue);

    ORIENTATION getOrientation() const;
    void setOrientation(const ORIENTATION &value);

    QGradientStops getGradientStops() const;
    void setGradientStops(const QGradientStops &gradientStops);

    double getVuLength() const;

private:
    double value;
    double peakValue;
    double vuLength;
    ORIENTATION orientation;
    void refreshVuLength();
protected:
    QLinearGradient gradient;
};

#endif // BAR_HPP
