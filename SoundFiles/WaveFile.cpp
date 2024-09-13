#include "WaveFile.h"
#include "../SoundBasis/Exceptions.h"

#include <string>

#include <iostream>

void WaveFile::readS8(std::ifstream& file){
  char tmp;
  while(buffer.S8.size() != buffer.S8.capacity()){
    file.read(&tmp,1);
    buffer.S8.push_back(tmp);
  }
}

void WaveFile::readS16(std::ifstream& file){
  short tmp;
  while(buffer.S16.size() != buffer.S16.capacity()){
    file.read((char*)&tmp,2);
    buffer.S16.push_back(tmp);
  }
}

void WaveFile::readS20(std::ifstream &file) {
  unsigned tmp;
  bool excessAtEnd = true;
  while(buffer.S20.size() != buffer.S20.capacity()){
    file.read((char*)&tmp,3);
    buffer.S20.push_back(tmp);

    if(excessAtEnd)
      file.putback( *(((char*)&tmp) + 2));

    excessAtEnd = not excessAtEnd;
  }
}

void WaveFile::readS24(std::ifstream &file) {
  unsigned tmp;
  while(buffer.S20.size() != buffer.S20.capacity()){
    file.read((char*)&tmp,3);
    buffer.S20.push_back(tmp);
  }
}

WaveFile::WaveFile(const std::string &filePath): riffHeader{}, waveHeader{}, waveFmtHeader{}, dataHeader{}{
  std::ifstream file(filePath, std::ios::binary);
  if(!file)
    throw std::runtime_error("Couldn't open file " + filePath);
  //read headers
  file.read((char*)&waveHeader,sizeof(waveHeader));

  do{
    file.ignore(riffHeader.size);
    file.read((char*)&riffHeader,sizeof(riffHeader));
  }while(std::string(riffHeader.id,3) != std::string("fmt") and not file.eof());
  if(file.eof())
    throw std::runtime_error("Couldn't find fmt header in " + filePath);

  file.read((char*)&waveFmtHeader,sizeof(waveFmtHeader));

  do{
    file.ignore(dataHeader.size);
    file.read((char*)&dataHeader,sizeof(dataHeader));
  }while(std::string(dataHeader.id,4) != std::string("data") and not file.eof());
  if(file.eof())
    throw std::runtime_error("Couldn't find data header in " + filePath);

  //prepare buffer to read data
  switch (waveFmtHeader.bits_per_sample) {
    case 16: sampleType = SampleType::S16;
      break;
    case 8: sampleType = SampleType::S8;
      break;
    case 20: sampleType = SampleType::S20;
      break;
    case 24:sampleType = SampleType::S24;
      break;
    default:throw SampleFormatError("unknown format");
  }

  size_t readBufsize = dataHeader.size / waveFmtHeader.block_align;
  //read data
  buffer = Buffer(sampleType,waveFmtHeader.num_channels * readBufsize);

  switch (sampleType) {
    case SampleType::S8:readS8(file);
      break;
    case SampleType::S16:readS16(file);
      break;
    case SampleType::S20:readS20(file);
      break;
    case SampleType::S24:readS24(file);
      break;
  }

}

Settings WaveFile::getSuggestedSettings() const {
  return Settings{(unsigned)waveFmtHeader.sample_rate,
                  sampleType,
                  DEFAULT_BUFFER_SIZE,
                  waveFmtHeader.num_channels};
}
