#ifndef FALLABLE_HPP
#define FALLABLE_HPP

template<class T>
class Fallable
{
public:
    Fallable();
    void setAcceleration(T acceleration);
    void setSpeed(T speed);
private:
    T accelerations;
    T initialSpeed;
    T currentSpeed;
    void init();
};

template<class T>
Fallable<T>::Fallable()
{
    init();
}

template<class T>
void Fallable<T>::setAcceleration(T acceleration)
{
    this->acceleration = acceleration;
}

template<class T>
void Fallable<T>::setSpeed(T speed)
{
    this->initialSpeed = speed;
    this->currentSpeed = speed;
}

template<class T>
void Fallable<T>::init()
{
    setSpeed(0);
    setAcceleration(0);
}

#endif // FALLABLE_HPP
