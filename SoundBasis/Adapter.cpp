#include "Adapter.h"

#include <limits>
#include <iostream>

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
    result.S16.push_back((short)sample);
  }

  return result;
}

Buffer monoToStereo(const Buffer& mono){
  Buffer stereo{SampleType::S16,mono.size() * 2};

  for(short sample : mono.S16){
    stereo.S16.push_back(sample);
    stereo.S16.push_back(sample);
  }

  return stereo;
}

Buffer S24toS16(const Buffer& origin){
  Buffer result{SampleType::S16,origin.size()};
  const double ratio = std::pow(2.,15) / std::pow(2.,23);

  for(unsigned sample24 : origin.S24){
     int sampleAsInt = *(int*)&sample24;
     sampleAsInt = (sampleAsInt << 8) / 256;
    result.S16.push_back(short(sample24 * ratio));
  }

  return result;
}

Buffer changeSampleRate(const Buffer& origin, Frequency originalRate, Frequency finalRate){
  const Real ratio = originalRate / finalRate;

  Buffer result(SampleType::S16,size_t((Real)origin.size() * ratio));

  double sampleNb = 0;
  while((size_t)sampleNb < origin.size()) {
    result.S16.push_back(origin.S16[(size_t)sampleNb]);
    sampleNb += ratio + std::numeric_limits<double>::epsilon();
  }

  return result;
}