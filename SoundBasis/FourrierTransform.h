#ifndef MUSICPLAYER_SOUNDBASIS_FOURRIERTRANSFORM_H_
#define MUSICPLAYER_SOUNDBASIS_FOURRIERTRANSFORM_H_

#include "Types.h"

Spectrum discretFourrierTransform(const RealBuffer& samples, Frequency samplingRate);

RealBuffer reconstruct(const Spectrum& spectrum, Frequency samplingRate, Time duration);

RealBuffer limitedReconstruct(const Spectrum& spectrum, Frequency samplingRate, Time duration, size_t wavesCount);

#endif //MUSICPLAYER_SOUNDBASIS_FOURRIERTRANSFORM_H_
