#ifndef FALLABLE_HPP
#define FALLABLE_HPP
#include "Parameters.hpp"

template<class T>
class Fallable
{
public:
    Fallable();
    void setAcceleration(T acceleration);
	void setInitialVelocity(T speed);
private:
	MovementParameters<T> fallingParameters;
	T currentFallingVelocity = T(0);
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
void Fallable<T>::setInitialVelocity(T initialVelocity)
{
	this->initialSpeed = initialVelocity;
}

template<class T>
void Fallable<T>::init()
{
	setInitialVelocity(0);
    setAcceleration(0);
}

#endif // FALLABLE_HPP
