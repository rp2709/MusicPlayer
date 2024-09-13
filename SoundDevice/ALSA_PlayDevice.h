#ifndef WAVE_PLAYER__ALSA_PLAYDEVICE_H_
#define WAVE_PLAYER__ALSA_PLAYDEVICE_H_

#include "BasePlayDevice.h"

#include <string>
#include <alsa/asoundlib.h>

class ALSA_PlayDevice : public BasePlayDevice{
  snd_pcm_t *playback_handle;
  snd_pcm_hw_params_t *hw_params;
 public:
  ALSA_PlayDevice();
  explicit ALSA_PlayDevice(const Settings& set, std::string name = "hw:0,0");
  ~ALSA_PlayDevice();
  void play(const Buffer& buffer);
  void stop();
  [[nodiscard]]bool isRunning()const;
  [[nodiscard]]bool ready()const;
  [[nodiscard]]size_t availableFrames()const;
};

#endif //WAVE_PLAYER__ALSA_PLAYDEVICE_H_
