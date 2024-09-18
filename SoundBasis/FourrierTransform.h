#ifndef MUSICPLAYER_SOUNDBASIS_FOURRIERTRANSFORM_H_
#define MUSICPLAYER_SOUNDBASIS_FOURRIERTRANSFORM_H_

#include "Types.h"
namespace DFT{
Spectrum discretFourrierTransform(const RealBuffer& samples, Frequency samplingRate);

RealBuffer reconstruct(const Spectrum& spectrum, Frequency samplingRate, Time duration);

RealBuffer limitedReconstruct(const Spectrum& spectrum, Frequency samplingRate, Time duration, size_t wavesCount);
}

namespace FFT {
Spectrum extractSpectrum(const RealBuffer &samples, Frequency samplingRate);

RealBuffer reconstruct(const Spectrum &spectrum);
}

#endif //MUSICPLAYER_SOUNDBASIS_FOURRIERTRANSFORM_H_
