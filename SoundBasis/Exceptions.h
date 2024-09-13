#ifndef WAVE_PLAYER__EXCEPTIONS_H_
#define WAVE_PLAYER__EXCEPTIONS_H_

#include <stdexcept>
#include <string>

struct DeviceSetupError:std::runtime_error{
  explicit DeviceSetupError(const std::string& message) : runtime_error(message){}
};

struct SampleFormatError : std::runtime_error{
  explicit SampleFormatError(const std::string &message) : std::runtime_error(message){}
};

struct BufferWriteError : std::runtime_error{
  explicit BufferWriteError(const std::string &message) : std::runtime_error(message){}
};


#endif //WAVE_PLAYER__EXCEPTIONS_H_
