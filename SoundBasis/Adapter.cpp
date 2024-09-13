#include "Adapter.h"

#include <limits>

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