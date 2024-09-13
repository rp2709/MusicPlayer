#include "ALSA_PlayDevice.h"
#include "../SoundBasis/Exceptions.h"

snd_pcm_format_t getSndFormat(SampleType sampleType){
  switch (sampleType) {
    case SampleType::S8:return SND_PCM_FORMAT_S8;
    case SampleType::S16:return SND_PCM_FORMAT_S16_LE;
    case SampleType::S20:return SND_PCM_FORMAT_S20_LE;
    case SampleType::S24:return SND_PCM_FORMAT_S24_LE;
  }
  throw SampleFormatError("Unknown format");
}

ALSA_PlayDevice::ALSA_PlayDevice(const Settings& set, std::string name) :
    BasePlayDevice(set),
    playback_handle(nullptr),
    hw_params(nullptr) {
  int err;

  if (snd_pcm_open(&playback_handle, name.data(), SND_PCM_STREAM_PLAYBACK, 0)< 0)
    throw DeviceSetupError("cannot open audio device " + name);

  snd_pcm_hw_params_malloc(&hw_params);

  if (snd_pcm_hw_params_any(playback_handle, hw_params) < 0)
    throw DeviceSetupError("cannot initialize hardware parameter structure " + name);

  if ((err = snd_pcm_hw_params_set_access(playback_handle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0)
    throw DeviceSetupError("cannot set access type " + std::string(snd_strerror(err)));


  SampleType candidateFormat = set.format;
  while((err = snd_pcm_hw_params_set_format(playback_handle, hw_params, getSndFormat(candidateFormat))) < 0){
    if(candidateFormat < SampleType::S24) {//there is at least one better quality option to test
      candidateFormat = SampleType(int(candidateFormat) + 1);
      if(candidateFormat == set.format)// we have explored all known formats
        throw DeviceSetupError("cannot set sample format " + std::string(snd_strerror(err)));
    }else{
      candidateFormat = SampleType::S8;
    }
  }
  settings.format = candidateFormat;

  if ((err = snd_pcm_hw_params_set_rate_near(playback_handle, hw_params, &settings.rate, nullptr)) < 0)
    throw DeviceSetupError("cannot set sample rate " + std::string(snd_strerror(err)));

  if ((err = snd_pcm_hw_params_set_channels(playback_handle, hw_params, settings.channels)) < 0)
    throw DeviceSetupError("cannot set channel count " + std::string(snd_strerror(err)));

  if ((err = snd_pcm_hw_params(playback_handle, hw_params)) < 0)
    throw DeviceSetupError("cannot set parameters " + std::string(snd_strerror(err)));

  snd_pcm_hw_params_free(hw_params);
}

void ALSA_PlayDevice::play(const Buffer &buffer) {
  if(settings.format != buffer.sampleType)
    throw SampleFormatError("This device is not configured for the buffer format");

  int err;
  snd_pcm_state_t deviceState = snd_pcm_state(playback_handle);
  if(deviceState != SND_PCM_STATE_RUNNING and deviceState != SND_PCM_STATE_PREPARED) {
    if ((err = snd_pcm_prepare(playback_handle)) < 0)
      throw DeviceSetupError("cannot prepare audio interface for use " + std::string(snd_strerror(err)));
  }
  err = snd_pcm_writei(playback_handle,buffer.S8.data(),buffer.size() / settings.channels);
  if(err < 0)
    throw BufferWriteError("ALSA error " + std::string(snd_strerror(err)));
}

ALSA_PlayDevice::~ALSA_PlayDevice() {
  snd_pcm_close (playback_handle);
}

bool ALSA_PlayDevice::ready() const {
  size_t availableFrames = snd_pcm_avail(playback_handle);
  return availableFrames >= settings.bufferSize;
}

void ALSA_PlayDevice::stop() {
  snd_pcm_drop(playback_handle);
}

size_t ALSA_PlayDevice::availableFrames() const {
  return snd_pcm_avail(playback_handle);
}

ALSA_PlayDevice::ALSA_PlayDevice():playback_handle(nullptr),hw_params(nullptr), BasePlayDevice(Settings{}){}
bool ALSA_PlayDevice::isRunning() const {
  return snd_pcm_state(playback_handle) == SND_PCM_STATE_RUNNING;
}
