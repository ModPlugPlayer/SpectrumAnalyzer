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
