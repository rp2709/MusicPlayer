#include "FourrierTransform.h"

Spectrum DFT::discretFourrierTransform(const RealBuffer& samples, Frequency samplingRate){
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

RealBuffer DFT::reconstruct(const Spectrum& spectrum, Frequency samplingRate, Time duration){
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

RealBuffer DFT::limitedReconstruct(const Spectrum& spectrum, Frequency samplingRate, Time duration, size_t wavesCount){
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


void fft(std::vector<Complex>& a, int exponentSign = 1) {
  const size_t N = a.size();
  if (N <= 1) return;

  std::vector<Complex> even(N / 2), odd(N / 2);
  for (size_t i = 0; i < N / 2; ++i) {
    even[i] = a[i * 2];
    odd[i] = a[i * 2 + 1];
  }

  fft(even);
  fft(odd);

  // Combine results
  for (size_t k = 0; k < N / 2; ++k) {
    Complex t = std::polar(1.0, exponentSign * 2 * M_PI * k / N) * odd[k];
    a[k] = even[k] + t;
    a[k + N / 2] = even[k] - t;
  }
}

size_t nextPowerOftwo(size_t x){
  size_t value = 1;
  while(value < x)value *= 2;
  return value;
}

Spectrum FFT::extractSpectrum(const RealBuffer& samples, Frequency samplingRate) {
  size_t N = nextPowerOftwo(samples.size());

  // Convert real-valued samples to complex-valued (imaginary part is 0)
  std::vector<Complex> complex_samples(N,{0,0});
  for (size_t i = 0; i < samples.size(); ++i) {
    complex_samples[i] = {samples[i], 0.0};
  }

  // Perform FFT on the complex samples
  fft(complex_samples);

  Spectrum result(N/2);

  // Calculate frequency, amplitude, and phase for each bin
  for (size_t k = 0; k < N / 2; ++k) {
    result[k].frequency = k * samplingRate / N; // Frequency in Hz
    result[k].amplitude = std::abs(complex_samples[k]) * 2.0 / samples.size(); // Amplitude
    result[k].phase = std::arg(complex_samples[k]); // Phase in radians
  }

  return result;
}

RealBuffer FFT::reconstruct(const Spectrum & spectrum){
  size_t N = spectrum.size() * 2;

  std::vector<Complex> complexSamples(N, {0.0, 0.0});

  for (size_t k = 0; k < N / 2; ++k) {
    complexSamples[k] = std::polar(spectrum[k].amplitude * N / 2, spectrum[k].phase);  // Convert to polar form
  }

  // Since FFT of a real-valued signal is symmetric, fill the second half with conjugates
  for (size_t k = 1; k < N / 2; ++k) {
    complexSamples[N - k] = std::conj(complexSamples[k]);
  }

  fft(complexSamples, -1);

  RealBuffer samples(N);
  for (size_t i = 0; i < N; ++i) {
    samples[i] = complexSamples[i].real() / N;
  }

  return samples;
}