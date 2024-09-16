#include "FourrierTransform.h"

FourrierValues discretFourrierTransform(const RealBuffer& samples, Frequency samplingRate){
  const Frequency step = samplingRate/ samples.size(); // equivalent to 1 / duration
  const size_t stepsNb = samples.size() / 2; // equivalent to (samplingRate / 2) / step
  const Complex i(0,1);
  const Real scale = 2 * M_PI / (Real)samples.size();

  FourrierValues spectrum(stepsNb);
#pragma omp parallel for
  for(size_t fi = 0; fi < stepsNb; ++fi){
    const Frequency testFrequency = (double)fi * step;
    Complex average(0,0);
    for(size_t si = 0; si < samples.size(); ++si){
      average += samples[si] * std::exp(-i * scale * (Real)si * (Real)fi);
    }
    average /= (Real)samples.size();
    spectrum[fi] = {testFrequency,average};
  }
  return spectrum;
}

RealBuffer reconstruct(const FourrierValues& spectrum, Frequency samplingRate, Time duration){
  RealBuffer samples;
  samples.reserve(samplingRate * duration);
  const Time period = 1/samplingRate;

  Time t = 0;
  while(t < duration){
    double sum = 0;
    for(const FourrierPair& value : spectrum){
      sum += 2 * value.second.real() * std::cos(2 * M_PI * value.first * t + std::arg(value.second));
    }
    samples.push_back(sum);
    t += period;
  }

  return samples;
}

