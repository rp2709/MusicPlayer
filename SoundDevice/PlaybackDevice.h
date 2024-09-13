#ifndef WAVE_PLAYER__PLAYBACKDEVICE_H_
#define WAVE_PLAYER__PLAYBACKDEVICE_H_

#include "ALSA_PlayDevice.h"

#ifdef __LINUX__
using PlaybackDevice = ALSA_PlayDevice;
#elif defined(_WIN64)
  #error "no support for Windows"
#elif defined(__APPLE__)
  #error "no support for macOS"
#endif

#endif //WAVE_PLAYER__PLAYBACKDEVICE_H_
