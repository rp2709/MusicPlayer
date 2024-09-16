#include "SoundBasis/FourrierTransform.h"
#include "SoundBasis/Adapter.h"
#include "SoundDevice/PlaybackDevice.h"
#include "SoundFiles/WaveFile.h"

#include <iostream>
#include <algorithm>

bool compareAmplitude(const PeriodicWave& p1, const PeriodicWave& p2){
  return p1.amplitude > p2.amplitude;
}

int main(){

  WaveFile wav("speech.wav");

  Settings settings = wav.getSuggestedSettings();
  const Real SR = wav.getSuggestedSettings().rate;

  wav.buffer = monoToStereo(wav.buffer);
  settings.channels = 2;

  RealBuffer samples = adapt(wav.buffer,settings);
  //RealBuffer samples = reconstruct({{50,0.25,0},{98,0.47,1.5}},SR,1);

  //FourrierValues spectrum = extractSpectrum(samples,120);
  Spectrum spectrum = discretFourrierTransform(samples,SR);

  std::sort(spectrum.begin(), spectrum.end(), compareAmplitude);

  RealBuffer reconstructedSamples = limitedReconstruct(spectrum,SR,2,1000);

  Buffer buffer = adapt(reconstructedSamples,SR,SampleType::S16);

  buffer = changeSampleRate(buffer,SR,44100);

  PlaybackDevice device({44100,SampleType::S16,4096,2});

  size_t chunkStart = 0;
  while(chunkStart < buffer.size()){
    while(not device.ready());
    device.play(buffer.getChunk(chunkStart,4096));
    chunkStart += 4096;
  }

  std::cin.ignore(1);
  return 0;
}