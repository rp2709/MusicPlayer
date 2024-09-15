#include "Adapter.h"

#include <limits>
#include <iostream>

Buffer adapt(const Buffer& origin, const Settings& originSettings, const Settings& resultSettings){
  Buffer result = origin;

  ///TODO: adapt format

  ///TODO: adapt sample rate
  if(originSettings.rate != resultSettings.rate){
    result.S16.clear();
    double ratio = (double)originSettings.rate / (double)resultSettings.rate;
    double sampleNb = 0;
    while((size_t)sampleNb < origin.size()) {
      result.S16.push_back(origin.S16[(size_t)sampleNb]);
      sampleNb += ratio + std::numeric_limits<double>::epsilon();
    }
  }
  ///TODO: adapt stereo/mono

  return result;
}

RealBuffer adapt(const Buffer& origin, const Settings& originSettings){
  RealBuffer result;
  result.reserve(origin.size() / originSettings.channels);

  if(originSettings.format != SampleType::S16) {
    Settings res = originSettings; res.format = SampleType::S16;
  }

  for(unsigned i = 0; i < origin.size(); i += originSettings.channels){
    Real convertedSample = origin.S16[i];
    if(originSettings.channels == 2){
      convertedSample += origin.S16[i + 1];
      convertedSample /= 2;
    }
    convertedSample /= (Real)std::numeric_limits<short>::max();
    result.push_back(convertedSample);
  }

  return result;
}

Buffer adapt(const RealBuffer& origin,Frequency sampleRate, SampleType resultFormat){
  Buffer result(SampleType::S16,origin.size() * 2);

  const Real shortMax = std::numeric_limits<short>::max();
  for(auto sample : origin){
    sample = (std::abs(sample) <= 1) ? sample * shortMax : std::signbit(sample) * shortMax;
    result.S16.push_back((short)sample);
  }

  return result;
}