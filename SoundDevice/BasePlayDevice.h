#ifndef WAVE_PLAYER__BASEPLAYDEVICE_H_
#define WAVE_PLAYER__BASEPLAYDEVICE_H_

#include "../SoundBasis/Types.h"
#include "../SoundBasis/Buffer.h"

class BasePlayDevice {
 protected:
  Settings settings;
 public:
  BasePlayDevice(const Settings& settings);
  [[nodiscard]]const Settings& getSettings()const;
};

#endif //WAVE_PLAYER__BASEPLAYDEVICE_H_
