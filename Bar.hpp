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

    inline void setSizes(const QSizeF &sizes);

    double getVuLength() const;

    inline void setDimmingPercentage(const unsigned char &dimmingPercentage);

    inline void setTransparencyPercentage(const unsigned char &transparencyPercentage);

private:
    double value;
    double peakValue;
    double vuLength;
    ORIENTATION orientation;
    void refresh();
    void refreshVuLength();
    void refreshDimmedGradient();
protected:
    QLinearGradient gradient;
    QLinearGradient dimmedGradient;
};

inline void Bar::setSizes(const QSizeF &sizes)
{
    Drawable::setSizes(sizes);
    gradient.setStart(0.0,sizes.height());
    gradient.setFinalStop(QPointF(0,0));
    dimmedGradient.setStart(0.0,sizes.height());
    dimmedGradient.setFinalStop(QPointF(0,0));
    refresh();
}

inline void Bar::setDimmingPercentage(const unsigned char &dimmingPercentage)
{
    Dimmable::setDimmingPercentage(dimmingPercentage);
    refresh();
}

inline void Bar::setTransparencyPercentage(const unsigned char &transparencyPercentage)
{
    Dimmable::setTransparencyPercentage(transparencyPercentage);
    refresh();
}

#endif // BAR_HPP
