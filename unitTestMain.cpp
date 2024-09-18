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
  Settings deviceSettings{44100,SampleType::S16,4096,2};
  PlaybackDevice device(deviceSettings);

  WaveFile wav("guitare.wav");

  Settings settings = wav.getSuggestedSettings();

  wav.buffer = S24toS16(wav.buffer);
  wav.buffer = monoToStereo(wav.buffer);
  //settings.channels = 2;

  //FourrierValues spectrum = extractSpectrum(samples,120);
  /*Spectrum spectrum = extractSpectrum(samples,SR);

  std::sort(spectrum.begin(), spectrum.end(), compareAmplitude);

  RealBuffer reconstructedSamples = limitedReconstruct(spectrum,SR,2,1000);*/

  wav.buffer = changeSampleRate(wav.buffer,settings.rate,deviceSettings.rate);

  size_t chunkStart = 0;
  while(chunkStart < wav.buffer.size()){

    Buffer chunk = wav.buffer.getChunk(chunkStart,deviceSettings.bufferSize);

    RealBuffer rchunk = adapt(chunk,deviceSettings);
    Spectrum spectrum = FFT::extractSpectrum(rchunk, deviceSettings.rate);
    std::sort(spectrum.begin(), spectrum.end(), compareAmplitude);
    std::cout << "Dominant frequency : " << spectrum.front().frequency << " Hz" << std::endl;

    while(not device.ready());
    device.play(chunk);
    chunkStart += deviceSettings.bufferSize;
  }

  std::cin.ignore(1);
  return 0;
}