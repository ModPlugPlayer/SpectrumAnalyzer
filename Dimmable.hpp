#ifndef DIMMABLE_HPP
#define DIMMABLE_HPP

class Dimmable {
public:
    Dimmable();
    inline unsigned char getDimmingPercentage() const;
    inline void setDimmingPercentage(unsigned const char &dimmingPercentage);

    inline unsigned char getTransparencyPercentage() const;
    inline void setTransparencyPercentage(unsigned const char &transparencyPercentage);

private:
    unsigned char dimmingPercentage;
    unsigned char transparencyPercentage;
};

inline unsigned char Dimmable::getDimmingPercentage() const {
    return dimmingPercentage;
}

inline void Dimmable::setDimmingPercentage(unsigned const char &dimmingPercentage) {
    this->dimmingPercentage = dimmingPercentage;
}


inline unsigned char Dimmable::getTransparencyPercentage() const {
    return transparencyPercentage;
}

inline void Dimmable::setTransparencyPercentage(const unsigned char &transparencyPercentage) {
    this->transparencyPercentage = transparencyPercentage;
}


#endif // DIMMABLE_HPP
