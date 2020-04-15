#ifndef DIMMABLE_HPP
#define DIMMABLE_HPP

class Dimmable
{
public:
    Dimmable();
    inline unsigned const char &getDimmingPercentage() const;
    inline void setDimmingPercentage(unsigned const char &value);

private:
    unsigned short dimmingPercentage;
};

inline unsigned const char & Dimmable::getDimmingPercentage() const
{
    return dimmingPercentage;
}

inline void Dimmable::setDimmingPercentage(unsigned const char &dimmingPercentage)
{
    this->dimmingPercentage = dimmingPercentage;
}

#endif // DIMMABLE_HPP
