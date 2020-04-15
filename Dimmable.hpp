#ifndef DIMMABLE_HPP
#define DIMMABLE_HPP

class Dimmable
{
public:
    Dimmable();
    inline double getDimmingPercentage() const;
    inline void setDimmingPercentage(double value);

private:
    double dimmingPercentage;
};

inline double Dimmable::getDimmingPercentage() const
{
    return dimmingPercentage;
}

inline void Dimmable::setDimmingPercentage(double value)
{
    dimmingPercentage = value;
}

#endif // DIMMABLE_HPP
