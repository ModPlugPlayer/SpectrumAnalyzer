#ifndef DIMMABLE_HPP
#define DIMMABLE_HPP

class Dimmable
{
public:
    Dimmable();
    inline unsigned short getDimmingPercentage() const;
    inline void setDimmingPercentage(unsigned short value);

private:
    unsigned short dimmingPercentage;
};

inline unsigned short Dimmable::getDimmingPercentage() const
{
    return dimmingPercentage;
}

inline void Dimmable::setDimmingPercentage(unsigned short value)
{
    dimmingPercentage = value;
}

#endif // DIMMABLE_HPP
