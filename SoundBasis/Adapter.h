#ifndef WAVE_PLAYER_SOUNDBASIS_ADAPTER_H_
#define WAVE_PLAYER_SOUNDBASIS_ADAPTER_H_

#include "Types.h"
#include "Buffer.h"

Buffer adapt(const Buffer& origin, const Settings& originSettings, const Settings& resultSettings);


#endif //WAVE_PLAYER_SOUNDBASIS_ADAPTER_H_
