#ifndef WAVE_PLAYER__MUSICPLAYER_H_
#define WAVE_PLAYER__MUSICPLAYER_H_

#include "../SoundDevice/PlaybackDevice.h"
#include "../SoundFiles/WaveFile.h"
#include "../SoundBasis/Adapter.h"

#include <thread>

struct State{
  bool isPlaying = false;
  Time currentTime = 0, songDuration = 0;
  Settings fileSettings{},deviceSettings{};
};

class MusicPlayer {
  State state;
  Buffer buffer;

  std::thread playBackThread;
  bool keepThreadRunning;

  size_t chunkStart;

  void playBack();
 public:
  MusicPlayer();
  ~MusicPlayer();

  void openFile(const std::string& filePath);

  void play();
  void pause();
  void stop();
  void restart();
  void setTime(const Time& time);

  [[nodiscard]]Time getTime()const;
};

#endif //WAVE_PLAYER__MUSICPLAYER_H_
