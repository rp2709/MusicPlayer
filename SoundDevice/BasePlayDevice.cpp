#include "BasePlayDevice.h"

BasePlayDevice::BasePlayDevice(const Settings &settings): settings(settings){}

const Settings &BasePlayDevice::getSettings() const {
  return settings;
}
