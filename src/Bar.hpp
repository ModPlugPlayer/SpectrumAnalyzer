#ifndef BAR_HPP
#define BAR_HPP
#include <QWidget>
#include "Enums.hpp"
#include "Drawable.hpp"
#include "Dimmable.hpp"
#include "Gradient.hpp"

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
    void refreshGradient();
    void refreshDimmedGradient();
protected:
    Gradient gradient;
    Gradient dimmedGradient;
    inline QColor getGradientColor(qreal key);
    inline QColor getDimmedGradientColor(qreal key);
};

inline QColor Bar::getGradientColor(qreal key) {
    gradient.getColor(key);
}

inline QColor Bar::getDimmedGradientColor(qreal key) {
    dimmedGradient.getColor(key);
}

inline void Bar::setSizes(const QSizeF &sizes)
{
    Drawable::setSizes(sizes);
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
