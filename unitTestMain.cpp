#include "SoundBasis/FourrierTransform.h"

int main(){

  FourrierValues spectrum{{20,{0.5,0}},{10,{1,0}},{24,{0.35,0}}};

  RealBuffer samples = reconstruct(spectrum,50,1);

  FourrierValues computedSpectrum = discretFourrierTransform(samples,50);

  return 0;
}