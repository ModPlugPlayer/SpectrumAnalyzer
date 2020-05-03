#ifndef DSP_HPP
#define DSP_HPP
#include <cmath>
#include <vector>

#define REAL 0
#define IMAG 1

class DSP
{
public:
    template<class T> static inline T *hanningMultipliers(size_t dataSize);
    template<class T> static inline T *hanningMultipliersMatlab(int N, short itype = 0);
    template<class T> static inline T *hanning(int windowLength);
    template<class T> static inline T calculateMagnitude(T real, T imaginary);
    template<class T> static inline T calculateMagnitudeDb(T real, T imaginary);
    template<class T> static inline T calculateMagnitudeDb(T magnitude);
    inline static void samplesTo10BandsFilter(double ** frequencyDomainData, float *filterOutputData, size_t sampleAmount);
};

// Inline Method Definitions

template <class T> inline T DSP::calculateMagnitudeDb(T magnitude)
{
    return log10(magnitude)*20;
}

template <> inline double DSP::calculateMagnitudeDb(double real, double imaginary)
{
    return 10*log10(real*real + imaginary*imaginary);
}

template <> inline float DSP::calculateMagnitudeDb(float real, float imaginary)
{
    return 10*log10f(real*real + imaginary*imaginary);
}

template <> inline long double DSP::calculateMagnitudeDb(long double real, long double imaginary)
{
    return 10*log10l(real*real + imaginary*imaginary);
}


template <class T> inline T DSP::calculateMagnitude(T real, T imaginary)
{
    return std::sqrt(real*real + imaginary*imaginary);
}


template <class T> inline T * DSP::hanningMultipliers(size_t dataSize){
    T *multipliers;

    multipliers = new T[dataSize];
    for (unsigned int i = 0; i < dataSize; i++) {
        T multiplier = 0.5 * (T(1) - cos(T(2)*M_PI*i/(dataSize-1)));
        multipliers[i] = multiplier;
    }
    return multipliers;
}

// Create a hamming window of windowLength samples in buffer
template<class T> inline T* DSP::hanning(int windowLength) {
    T *buffer = new T[windowLength];
    for(int i = 0; i < windowLength; i++) {
        buffer[i] = 0.54 - (0.46 * cos( 2 * M_PI * (i / ((windowLength - 1) * 1.0))));
    }
    return buffer;
}

/*  function w = hanning(varargin)
%   HANNING   Hanning window.
%   HANNING(N) returns the N-point symmetric Hanning window in a column
%   vector.  Note that the first and last zero-weighted window samples
%   are not included.
%
%   HANNING(N,'symmetric') returns the same result as HANNING(N).
%
%   HANNING(N,'periodic') returns the N-point periodic Hanning window,
%   and includes the first zero-weighted window sample.
%
%   NOTE: Use the HANN function to get a Hanning window which has the
%          first and last zero-weighted samples.ep
    itype = 1 --> periodic
    itype = 0 --> symmetric
    default itype=0 (symmetric)

    Copyright 1988-2004 The MathWorks, Inc.
%   $Revision: 1.11.4.3 $  $Date: 2007/12/14 15:05:04 $
*/
template <class T> inline T * DSP::hanningMultipliersMatlab(int N, short itype){
    int half, i, idx, n;
    T *w;

    w = new T[N];
    std::fill(w, w+N, T(0));

    if(itype==1)    //periodic function
        n = N-1;
    else
        n = N;

    if(n%2==0)
    {
        half = n/2;
        for(i=0; i<half; i++) //CALC_HANNING   Calculates Hanning window samples.
            w[i] = 0.5 * (T(1) - cos(T(2)*M_PI*(i+1) / (n+1)));

        idx = half-1;
        for(i=half; i<n; i++) {
            w[i] = w[idx];
            idx--;
        }
    }
    else
    {
        half = (n+1)/2;
        for(i=0; i<half; i++) //CALC_HANNING   Calculates Hanning window samples.
            w[i] = 0.5 * (T(1) - cos(T(2)*M_PI*(i+1) / (n+1)));

        idx = half-2;
        for(i=half; i<n; i++) {
            w[i] = w[idx];
            idx--;
        }
    }

    if(itype==1)    //periodic function
    {
        for(i=N-1; i>=1; i--)
            w[i] = w[i-1];
        w[0] = 0.0;
    }
    return w;
}

void DSP::samplesTo10BandsFilter(double ** frequencyDomainData, float *filterOutputData, size_t sampleAmount) {
    float band_power=0.0;
    float harmonic_amplitude=0.0;
    size_t i, out_index;

    out_index=0;

    for (i = 0; i < sampleAmount/2+1; i++) {
        //Replaced by or below
        // end_band_index=0;                   // Banda di freq   Frequenza centrale
        // if (i==1) end_band_index=1;         // 22Hz-44Hz            31.5Hz
        // else if (i==2) end_band_index=1;    // 44Hz-88Hz            63Hz
        // else if (i==4) end_band_index=1;    // 88Hz-177Hz           125Hz
        // else if (i==8) end_band_index=1;    // 177Hz-355Hz          250Hz
        // else if (i==17) end_band_index=1;   // 355Hz-710Hz          500Hz
        // else if (i==33) end_band_index=1;   // 710Hz-1420Hz         1000Hz
        // else if (i==66) end_band_index=1;   // 1420Hz-2840Hz        2000Hz
        // else if (i==132) end_band_index=1;  // 2840Hz-5680Hz        4000Hz
        // else if (i==264) end_band_index=1;  // 5680Hz-11360Hz       8000Hz
        // else if (i==511) end_band_index=1;  // 11360Hz-22050Hz      16000Hz
        //if (end_band_index==1)

        if (i==1||i==2||i==4||i==8||i==17||i==33||i==66||i==132||i==264||i==511) {
            filterOutputData[out_index]=band_power; //Memorizzo la potenza di banda
            band_power=0; //Azzero il contatore di potenza della banda
            out_index++;  //Incremento l'indice che indica la barra (va da 0 a 9)
        }
        //Calcolo l'ampiezza dell'armonica (che costituisc una sorta di potenza di armonica)
        harmonic_amplitude = calculateMagnitude<double>(frequencyDomainData[i][REAL],frequencyDomainData[i][IMAG]);
        //Aggiungo la potenza dell'armonica alla potenza della banda a cui l'armonica appartiene
        band_power+=harmonic_amplitude;

    }

return;
}

#endif // DSP_HPP
