#include "SoundBasis/FourrierTransform.h"
#include "SoundBasis/Adapter.h"
#include "SoundDevice/PlaybackDevice.h"

#include <iostream>

int main(){
  PlaybackDevice device({44100,SampleType::S16,4096,2});

  FourrierValues spectrum{{750,{0.5}},{500,{0.5}}};

  RealBuffer samples = reconstruct(spectrum,44100,1);

  Buffer buffer = adapt(samples,44100,SampleType::S16);

  for(size_t chunkStart = 0; chunkStart < buffer.size(); chunkStart += 4096){
    while(not device.ready());
    device.play(buffer.getChunk(chunkStart,4096));
  }

  //FourrierValues computedSpectrum = discretFourrierTransform(samples,50);

  std::cin.ignore(1);
  return 0;
}