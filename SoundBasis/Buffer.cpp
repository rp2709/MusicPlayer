#include "Buffer.h"
#include "Exceptions.h"

Buffer::~Buffer(){
  switch (sampleType) {
    case SampleType::S8:std::destroy(S8.begin(), S8.end());
      break;
    case SampleType::S16:std::destroy(S16.begin(), S16.end());
      break;
    case SampleType::S20:std::destroy(S20.begin(), S20.end());
      break;
    case SampleType::S24:std::destroy(S24.begin(), S24.end());
      break;
  }
}

Buffer::Buffer(SampleType sampleType, size_t bufferSize):sampleType(sampleType),S8(){
  switch (sampleType) {
    case SampleType::S8:S8.reserve(bufferSize);
      break;
    case SampleType::S16:S16.reserve(bufferSize);
      break;
    case SampleType::S20:S20.reserve(bufferSize);
      break;
    case SampleType::S24:S24.reserve(bufferSize);
      break;
    default:
      throw SampleFormatError("unknown format");
  }
}

Buffer &Buffer::operator=(Buffer &&tmp_other)  noexcept {
  this->~Buffer();
  S8 = std::move(tmp_other.S8);
  sampleType = tmp_other.sampleType;
  return *this;
}

size_t Buffer::size() const {
  switch (sampleType) {
    case SampleType::S8:return S8.size();
    case SampleType::S16:return S16.size();
    case SampleType::S20:return S20.size();
    case SampleType::S24:return S24.size();
  }
  throw SampleFormatError("unknown format");
}

Buffer Buffer::getChunk(size_t pos, size_t n) const {
  if(pos >= size())
    throw std::out_of_range("Pos outside of buffer");

  n = (pos + n > size()) ? size() - pos : n;

  Buffer chunk(sampleType,n);
  chunk.setSize(n);

  switch (sampleType) {
    case SampleType::S8: std::copy(S8.begin() + pos, S8.begin() + pos + n, chunk.S8.begin());
      break;
    case SampleType::S16: std::copy(S16.begin() + pos, S16.begin() + pos + n, chunk.S16.begin());
      break;
    case SampleType::S20: std::copy(S20.begin() + pos, S20.begin() + pos + n, chunk.S20.begin());
      break;
    case SampleType::S24: std::copy(S24.begin() + pos, S24.begin() + pos + n, chunk.S24.begin());
      break;
    default:
      throw SampleFormatError("unknown format");
  }
  return chunk;
}

void Buffer::setSize(size_t size) {
  switch (sampleType) {
    case SampleType::S8:S8.resize(size);
      break;
    case SampleType::S16:S16.resize(size);
      break;
    case SampleType::S20:S20.resize(size);
      break;
    case SampleType::S24:S24.resize(size);
      break;
    default:
      throw SampleFormatError("unknown format");
  }
}
Buffer &Buffer::operator=(const Buffer &other) {
  this->sampleType = other.sampleType;
  this->S8 = other.S8;
  return *this;
}
Buffer::Buffer(const Buffer &other):Buffer(){
  *this = other;
}
