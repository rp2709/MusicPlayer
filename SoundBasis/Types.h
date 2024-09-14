#ifndef WAVE_PLAYER__TYPES_H_
#define WAVE_PLAYER__TYPES_H_

#include <vector>
#include <complex>

enum class SampleType{S8,S16,S20,S24};
using Sample8 = signed char;
using Sample16 = short;
using Sample20 = unsigned;
using Sample24 = unsigned;

using SampleRate = unsigned int;

struct Settings{
  SampleRate rate = 44100;
  SampleType format = SampleType::S16;
  size_t bufferSize = 4096;
  int channels = 2; //1 mono, 2 stereo
};

using Time = double;

using Complex = std::complex<double>;
using FourrierValues = std::vector<Complex>;
using RealBuffer = std::vector<double>;
using Frequency = double;

#endif //WAVE_PLAYER__TYPES_H_
