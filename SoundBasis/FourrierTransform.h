#ifndef MUSICPLAYER_SOUNDBASIS_FOURRIERTRANSFORM_H_
#define MUSICPLAYER_SOUNDBASIS_FOURRIERTRANSFORM_H_

#include "Types.h"

FourrierValues discretFourrierTransform(const RealBuffer& samples, Frequency samplingRate);

RealBuffer reconstruct(const FourrierValues& spectrum, Frequency samplingRate, Time duration);

#endif //MUSICPLAYER_SOUNDBASIS_FOURRIERTRANSFORM_H_
