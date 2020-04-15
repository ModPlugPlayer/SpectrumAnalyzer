#ifndef DIMMABLE_HPP
#define DIMMABLE_HPP

class Dimmable
{
public:
    Dimmable();
    inline unsigned char getDimmingPercentage() const;
    inline void setDimmingPercentage(unsigned char value);

private:
    unsigned short dimmingPercentage;
};

inline unsigned char Dimmable::getDimmingPercentage() const
{
    return dimmingPercentage;
}

inline void Dimmable::setDimmingPercentage(unsigned char value)
{
    dimmingPercentage = value;
}

#endif // DIMMABLE_HPP
