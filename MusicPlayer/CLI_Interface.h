#ifndef WAVE_PLAYER_MUSICPLAYER_CLI_INTERFACE_H_
#define WAVE_PLAYER_MUSICPLAYER_CLI_INTERFACE_H_

#include "MusicPlayer.h"
#include <vector>

class CLI_Interface {
  MusicPlayer player;
  static int instances;

  const std::vector<std::string> COMMANDS{"exit","help","play", "pause", "stop", "restart", "Time", "open", "setTime"};
  enum class CommandId{exit,help,play,pause,stop,restart,Time,open,setTime};

  void help();
  void open(const std::string& filePath);
 public:
  CLI_Interface();
  void run();
};

#endif //WAVE_PLAYER_MUSICPLAYER_CLI_INTERFACE_H_
