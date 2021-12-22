/*
Fallable class declarations and definitions of Spectrum Analyzer
Copyright (C) 2020 Volkan Orhan

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this library; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

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
