#ifndef WAVE_PLAYER__WAVEFILE_H_
#define WAVE_PLAYER__WAVEFILE_H_

#include <string>
#include <cstdint>
#include <fstream>

#include "../SoundBasis/Buffer.h"

#define DEFAULT_BUFFER_SIZE 4096

struct WaveHeader
{
  char chunk_id[4];
  int chunk_size;
  char format[4];
}__attribute__((__packed__));

struct RiffChunkHeader
{
  char id[4];
  int size;
}__attribute__((__packed__));

struct WaveFmtChunk
{
  short audio_format;
  short num_channels;
  int sample_rate;
  int byte_rate;
  short block_align;
  short bits_per_sample;
}__attribute__((__packed__));

class WaveFile {
  RiffChunkHeader riffHeader;
  WaveFmtChunk waveFmtHeader;
  WaveHeader waveHeader;
  RiffChunkHeader dataHeader;
  SampleType sampleType;

  void readS8(std::ifstream& file);
  void readS16(std::ifstream& file);
  void readS20(std::ifstream& file);
  void readS24(std::ifstream& file);

 public:
  explicit WaveFile(const std::string &filePath);
  Buffer buffer;
  [[nodiscard]]Settings getSuggestedSettings()const;
};

#endif //WAVE_PLAYER__WAVEFILE_H_
