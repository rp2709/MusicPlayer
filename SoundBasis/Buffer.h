#ifndef WAVE_PLAYER__BUFFER_H_
#define WAVE_PLAYER__BUFFER_H_

#include "Types.h"

template<typename T>
using RunTimeBuffer = std::vector<T>;

struct Buffer {
  SampleType sampleType;
  union {
    RunTimeBuffer<Sample8> S8;
    RunTimeBuffer<Sample16> S16;
    RunTimeBuffer<Sample20> S20;
    RunTimeBuffer<Sample24> S24;
  };

  void setSize(size_t size);

  [[nodiscard]]size_t size()const;
  [[nodiscard]]Buffer getChunk(size_t pos, size_t n)const;

  Buffer& operator = (Buffer&& tmp_other) noexcept ;
  Buffer& operator = (const Buffer& other);

  Buffer():Buffer(SampleType::S8,0){}
  Buffer(SampleType sampleType, size_t bufferSize);
  Buffer(const Buffer& other);
  ~Buffer();
};

#endif //WAVE_PLAYER__BUFFER_H_
