#ifndef BAR_HPP
#define BAR_HPP
#include <QFrame>
#include "Enums.hpp"
#include <QWidget>
#include <QGridLayout>
#include "Dimmable.hpp"

class Bar : public QFrame, public Dimmable
{
public:
    Bar(QWidget *parent = nullptr);

    double getValue();

    double getPeakValue();
    void setPeakValue(const double &peakValue);

    ORIENTATION getOrientation() const;
    void setOrientation(const ORIENTATION &value);

    QGradientStops getGradientStops() const;
    void setGradientStops(const QGradientStops &gradientStops);

    double getVuLength() const;

    inline void setDimmingPercentage(const unsigned char &dimmingPercentage);

    inline void setTransparencyPercentage(const unsigned char &transparencyPercentage);

    inline void resizeEvent(QResizeEvent *event);

public slots:
    void setValue(const double value);

private:
    double value;
    double peakValue;
    double vuLength;
    ORIENTATION orientation;
    void refresh();
    void refreshVuLength();
    void refreshGradient();
    void refreshDimmedGradient();
    void initUI();
    QWidget *widget;
protected:
    QLinearGradient gradient;
    QLinearGradient dimmedGradient;
};

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

inline void Bar::resizeEvent(QResizeEvent *event){

    refresh();
}

#endif // BAR_HPP
