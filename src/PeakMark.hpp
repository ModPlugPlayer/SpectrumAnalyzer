/*
PeakMark class declarations and definitions of Spectrum Analyzer
Copyright (C) 2020 Volkan Orhan

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this library; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#ifndef PEAKMARK_HPP
#define PEAKMARK_HPP
#include <algorithm>

template<class T>
class PeakMark
{
public:
    PeakMark();
    inline void setPeakMarkEnabled(bool enabled);
    bool isPeakMarkEnabled() const;

    inline void setPeakMarkValue(T value);
    T getPeakMarkValue() const;

    inline size_t getLifeTime() const;
    inline void setLifeTime(const size_t lifeTimeMiliseconds);
private:
    T peakMarkValue;
    bool peakMarkEnabled = false;
    size_t lifeTime;
};

template<class T>
inline void PeakMark<T>::setPeakMarkEnabled(bool enabled)
{
    peakMarkEnabled = enabled;
}

template<class T>
inline void PeakMark<T>::setPeakMarkValue(T value)
{
    peakMarkValue = value;
}

template<class T>
inline size_t PeakMark<T>::getLifeTime() const
{
    return lifeTime;
}

template<class T>
inline void PeakMark<T>::setLifeTime(const size_t lifeTimeMiliseconds)
{
    lifeTime = lifeTimeMiliseconds;
}

template<class T>
inline T PeakMark<T>::getPeakMarkValue() const
{
return peakMarkValue;
}

template<class T>
inline bool PeakMark<T>::isPeakMarkEnabled() const
{
    return peakMarkEnabled;
}

#endif // PEAKMARK_HPP
