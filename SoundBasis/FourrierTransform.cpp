#include "FourrierTransform.h"
FourrierTransform::FourrierTransform(const RealBuffer &buffer, Frequency samplingFreq):freqMax(samplingFreq/2),duration(buffer.size()/samplingFreq){
  step = 1./duration;

  Frequency testFreq = 0;
  while(testFreq <= freqMax){
    Complex sum(0,0);
    const Complex I(0,1);
    for(unsigned i = 0; i < buffer.size(); ++i){
      const Time t = i / samplingFreq;
      sum += (buffer[i]/(double)buffer.size()) * std::exp(-2 * M_PI * I * testFreq * t);
    }
    values.push_back(sum);
    testFreq += step;
  }
}

RealBuffer FourrierTransform::reconstruct(Frequency samplingFreq) const {
  RealBuffer buffer;
  const Time period = 1/samplingFreq;

  Time t = 0;
  while(t < duration){
    double sum = 0;
    for(unsigned i = 0; i < values.size(); ++i){
      const Frequency frequency = i * step;
      const Complex& value = values[i];
      sum += value.real() * std::sin(2 * M_PI * frequency * t + std::arg(value));
    }
    buffer.push_back(sum);
    t += period;
  }

  return buffer;
}


