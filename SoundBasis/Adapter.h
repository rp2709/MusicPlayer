#ifndef WAVE_PLAYER_SOUNDBASIS_ADAPTER_H_
#define WAVE_PLAYER_SOUNDBASIS_ADAPTER_H_

#include "Types.h"
#include "Buffer.h"

RealBuffer adapt(const Buffer& origin, const Settings& originSettings);

Buffer adapt(const RealBuffer& origin,Frequency sampleRate,SampleType resultFormat);

Buffer monoToStereo(const Buffer& mono);

Buffer S24toS16(const Buffer& origin);

Buffer changeSampleRate(const Buffer& origin, Frequency originalRate, Frequency finalRate);


#endif //WAVE_PLAYER_SOUNDBASIS_ADAPTER_H_
