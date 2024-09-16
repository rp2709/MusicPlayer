#include "FourrierTransform.h"

Spectrum discretFourrierTransform(const RealBuffer& samples, Frequency samplingRate){
  const Frequency step = samplingRate/ samples.size(); // equivalent to 1 / duration
  const size_t stepsNb = samples.size() / 2; // equivalent to (samplingRate / 2) / step
  const Complex i(0,1);
  const Real scale = 2 * M_PI / (Real)samples.size();

  Spectrum spectrum(stepsNb);
#pragma omp parallel for
  for(size_t fi = 0; fi < stepsNb; ++fi){
    const Frequency testFrequency = (double)fi * step;
    Complex average(0,0);
    for(size_t si = 0; si < samples.size(); ++si){
      average += samples[si] * std::exp(-i * scale * (Real)si * (Real)fi);
    }
    average /= (Real)samples.size();

    spectrum[fi].frequency = testFrequency;
    spectrum[fi].amplitude = 2 * std::abs(average);
    spectrum[fi].phase = std::arg(average);
  }
  return spectrum;
}

RealBuffer reconstruct(const Spectrum& spectrum, Frequency samplingRate, Time duration){
  RealBuffer samples;
  samples.reserve(samplingRate * duration);
  const Time period = 1/samplingRate;
  const Real TAU = 2 * M_PI;

  Time t = 0;
  while(t < duration){
    double sum = 0;
    for(const PeriodicWave& wave : spectrum){
      sum += wave.amplitude * std::cos(TAU * wave.frequency * t + wave.phase);
    }
    samples.push_back(sum);
    t += period + std::numeric_limits<Real>::epsilon();
  }

  return samples;
}

RealBuffer limitedReconstruct(const Spectrum& spectrum, Frequency samplingRate, Time duration, size_t wavesCount){
  RealBuffer samples;
  samples.reserve(samplingRate * duration);
  const Time period = 1/samplingRate;
  const Real TAU = 2 * M_PI;

  Time t = 0;
  while(t < duration){
    double sum = 0;
    for(size_t i = 0; i < std::min(wavesCount,spectrum.size()); ++i){
      sum += spectrum[i].amplitude * std::cos(TAU * spectrum[i].frequency * t + spectrum[i].phase);
    }
    samples.push_back(sum);
    t += period + std::numeric_limits<Real>::epsilon();
  }

  return samples;
}