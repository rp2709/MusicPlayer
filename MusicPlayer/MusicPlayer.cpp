#include "MusicPlayer.h"

#include "../SoundBasis/Adapter.h"

#include <iostream>
#include <chrono>

MusicPlayer::MusicPlayer() : state{}, playBackThread(&MusicPlayer::playBack, this), chunkStart(0),keepThreadRunning(true) {}

MusicPlayer::~MusicPlayer() {
  keepThreadRunning = false;
  if(playBackThread.joinable())
    playBackThread.join();
}

void MusicPlayer::openFile(const std::string &filePath) {
  keepThreadRunning = false;
  if(playBackThread.joinable())
    playBackThread.join();

  WaveFile wav(filePath);
  state = State{};
  state.fileSettings = wav.getSuggestedSettings();
  buffer = std::move(wav.buffer);

  keepThreadRunning = true;
  playBackThread = std::thread(&MusicPlayer::playBack, this);
}

void MusicPlayer::play() {
  state.isPlaying = true;
}

void MusicPlayer::pause() {
  state.isPlaying = false;
}

void MusicPlayer::playBack() {
  using std::chrono::steady_clock;

  PlaybackDevice soundDevice(state.fileSettings);
  state.deviceSettings = soundDevice.getSettings();

  buffer = adapt(buffer, state.fileSettings, state.deviceSettings);

  state.songDuration = ((double) buffer.size() / state.deviceSettings.channels) / state.deviceSettings.rate;
  const Time sleepTimeMs =
      (double) state.deviceSettings.bufferSize / state.deviceSettings.channels / state.deviceSettings.rate / 1000;

  chunkStart = 0;
  state.currentTime = 0;
  std::chrono::time_point previous = steady_clock::now();

  while (keepThreadRunning) {
    if (not state.isPlaying) {
      if (soundDevice.isRunning())
        soundDevice.stop();
      chunkStart = size_t(state.currentTime * state.deviceSettings.rate * state.deviceSettings.channels);
      std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(50));
      previous = steady_clock::now();
      continue;
    }

    if(state.currentTime < state.songDuration) {
      state.currentTime += std::chrono::duration<double, std::ratio<1, 1>>(steady_clock::now() - previous).count();
      previous = steady_clock::now();
    }

    if (chunkStart >= buffer.size()) {
      std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(50));
      continue;
    }

    while (not soundDevice.ready());
    soundDevice.play(buffer.getChunk(chunkStart, state.deviceSettings.bufferSize));
    std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(sleepTimeMs));
    chunkStart += state.deviceSettings.bufferSize;
  }
}

void MusicPlayer::stop() {
  pause();
  state.currentTime = 0;
  std::this_thread::sleep_for(std::chrono::duration<int,std::milli>(50));
}

void MusicPlayer::restart() {
  stop();
  play();
}

void MusicPlayer::setTime(const Time &time) {
  stop();
  state.currentTime = time;
  std::this_thread::sleep_for(std::chrono::duration<int,std::milli>(50));
  play();
}
Time MusicPlayer::getTime() const {
  return state.currentTime;
}