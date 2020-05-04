#ifndef DSP_HPP
#define DSP_HPP
#include <cmath>
#include <vector>

#define REAL 0
#define IMAG 1

template <class T>
struct OctaveBand {
    T midBandFrequency;
    T nominalMidbandFrequency;
    T upperEdgeFrequency;
    T lowerEdgerequency;
};

enum OctaveBandBase{
    Base2 = 2,
    Base10 = 10
};

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
    template <class T> static inline std::vector<OctaveBand<T>> calculateOctaveBands(OctaveBandBase base, size_t nthOctave);
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

    //31 Band:
    //20    31.5   50   80    125   200   315   500   800   1.25k   2k   3.15k   5k   8k    12.5k   20k
    //25    40     63   100   160   250   400   630   1k    1.6k   2.5k   4k    6.3k  10k     16k

    //https://books.google.com.tr/books?id=bbNfr_bwUXwC&pg=PA40&lpg=PA40&dq=8va+bands&source=bl&ots=XKR3UPdzRZ&sig=ACfU3U0t6yWk6WKQMaqV74llNF6EY0kxCQ&hl=en&sa=X&ved=2ahUKEwirhtL5jJjpAhUPesAKHaV9CP4Q6AEwDHoECAkQAQ#v=onepage&q=8va%20bands&f=false
    //https://soundbridge.io/spectrum-analyzer
    //⅓ 8va bands
    //1, 1.25, 1.63, 2, 2.5, 3.15, 4, 5, 6.3, 8, 10, 12.5, 16.3, 20, 25, 31.5, 40, 50, 63, 80, 100, 125, 163, 200, 250, 315, 400, 500, 630, 800, 1000, 1250, 1630, 2k, 2500, 3150, 4k, 5k, 6300, 8k, 10k, 12,5k 16k, 20k, etc; as necessary

    //8va bands

    //31.5, 63, 125, 250, 500, 1000, 2k, 4k, 8k, 16k, etc; as necessary

    //https://en.wikipedia.org/wiki/Octave_band

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

/*
%% Calculate Third Octave Bands (base 2) in Matlab
fcentre  = 10^3 * (2 .^ ([-18:13]/3))
fd = 2^(1/6);
fupper = fcentre * fd
flower = fcentre / fd

Base 10 calculation

%% Calculate Third Octave Bands (base 10) in Matlab
fcentre = 10.^(0.1.*[12:43])
fd = 10^0.05;
fupper = fcentre * fd
flower = fcentre / fd
*/
template <class T> std::vector<OctaveBand<T>> calculateOctaveBandsWikipedia(OctaveBandBase base, size_t nthOctave) {
    std::vector<OctaveBand<T>> octaveBands;
    T fd;
    T i = 0;
    switch (base) {
        case OctaveBandBase::Base2:
            fd = pow(T(2),T(1)/T(2*nthOctave));
            i=T(-6);
            while(true) {
                OctaveBand<T> octaveBand;
                octaveBand.midBandFrequency = pow(T(2), T(i)) * T(1000);
                octaveBand.upperEdgeFrequency = octaveBand.midBandFrequency * fd;
                octaveBand.lowerEdgerequency = octaveBand.midBandFrequency / fd;
                if(octaveBand.midBandFrequency > T(23000))
                    break;
                octaveBands.push_back(octaveBand);
                i += T(1)/nthOctave;
            }
            break;
        case OctaveBandBase::Base10:
            fd = pow(T(10),T(0.05));
            while(true) {
                OctaveBand<T> octaveBand;
                octaveBand.midBandFrequency = pow(T(10), T(0.1) * i);
                octaveBand.upperEdgeFrequency = octaveBand.midBandFrequency * fd;
                octaveBand.lowerEdgerequency = octaveBand.midBandFrequency / fd;
                if(octaveBand.midBandFrequency > T(23000))
                    break;
                octaveBands.push_back(octaveBand);
                i = i+1;
            }
            break;
    }
    return octaveBands;
}

/*
 * "ANSI S1.11: Specification for Octave, Half-Octave, and Third Octave Band Filter Sets" (PDF). Retrieved 7 March 2018.
 */
template<class T> inline std::vector<OctaveBand<T>> DSP::calculateOctaveBands(OctaveBandBase base, size_t nthOctave) {
    T G; //octave ratio
    T fm; //exact midband frequency
    switch (base) {
        case OctaveBandBase::Base2:
            G = T(2);
            break;
        case OctaveBandBase::Base10:
            G = pow(T(10), T(3)/T(10));
    }
    size_t b = nthOctave; //bandwidth designator
    T fr = 1000; //reference frequency
    std::vector<OctaveBand<T>> octaveBands;
    T fd;
    T i = 0;

    while(true) {
        OctaveBand<T> octaveBand;
        if(b%2 == 1) {
            fm = pow(G, (i-T(30))/b)*fr;
        }
        else {
            fm = pow(G, (T(2)*i-T(59))/(b*T(2)))*fr;
        }
        octaveBand.midBandFrequency = fm;
        octaveBand.lowerEdgerequency = pow(G, T(-1) / T(2) * b) * fm;
        octaveBand.upperEdgeFrequency = pow(G, T(1) / T(2) * b) * fm;
        if(octaveBand.midBandFrequency > T(23000))
            break;
        octaveBands.push_back(octaveBand);
        i += T(1);
    }

    return octaveBands;
}

#endif // DSP_HPP
