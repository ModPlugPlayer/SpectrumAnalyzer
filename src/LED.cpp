#include "LED.hpp"

LED::LED()
{

}

void LED::refreshColor()
{

}

void LED::refreshDimmedColor()
{
    int alpha = (100-getTransparencyPercentage())*255/100;
    dimmedColor = color.lighter(100-getDimmingPercentage());
    dimmedColor.setAlpha(alpha);
}
