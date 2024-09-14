#ifndef MUSICPLAYER_SOUNDBASIS_FOURRIERTRANSFORM_H_
#define MUSICPLAYER_SOUNDBASIS_FOURRIERTRANSFORM_H_

#include "Types.h"

class FourrierTransform {
  FourrierValues values;
  Frequency freqMax;
  Frequency step;
  Time duration;
 public:
  FourrierTransform(const RealBuffer& buffer, Frequency samplingFreq);
  [[nodiscard]]RealBuffer reconstruct(Frequency samplingFreq)const;
};

#endif //MUSICPLAYER_SOUNDBASIS_FOURRIERTRANSFORM_H_
