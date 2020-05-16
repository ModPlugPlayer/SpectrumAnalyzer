#ifndef PEAKMARK_HPP
#define PEAKMARK_HPP

template<class T>
class PeakMark
{
public:
    PeakMark();
    inline void setPeakMark(T enabled);
    inline void setPeakMarkValue(T value);
private:
    T peakMarkValue;
    T peakMarkEnabled = false;
};

template<class T>
inline void PeakMark<T>::setPeakMark(T enabled)
{
    peakMarkEnabled = enabled;
}

template<class T>
inline void PeakMark<T>::setPeakMarkValue(T value)
{
    peakMarkValue = value;
}

#endif // PEAKMARK_HPP
