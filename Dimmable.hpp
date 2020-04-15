#ifndef DIMMABLE_HPP
#define DIMMABLE_HPP

class Dimmable
{
public:
    Dimmable();
    inline unsigned char getDimmingPercentage() const;
    inline void setDimmingPercentage(unsigned const char &dimmingPercentage);

    inline bool isDimmable() const;
    inline void setDimmable(const bool &dimmable);

private:
    unsigned short dimmingPercentage;
    bool dimmable;
};

inline unsigned char Dimmable::getDimmingPercentage() const
{
    return dimmingPercentage;
}

inline void Dimmable::setDimmingPercentage(unsigned const char &dimmingPercentage)
{
    this->dimmingPercentage = dimmingPercentage;
}

inline bool Dimmable::isDimmable() const
{
    return dimmable;
}

inline void Dimmable::setDimmable(const bool &dimmable)
{
    this->dimmable = dimmable;
}

#endif // DIMMABLE_HPP
