#include "CLI_UI/CLI_UI.h"
#include "MusicPlayer/MusicPlayer.h"

int main (){
  MusicPlayer player;
  CLI_UI ui;

  ui.addElement<UI_ELEMENTS::BUTTON>(
      new Button("",player,&MusicPlayer::play,&MusicPlayer::pause,"pause","play"));

  ui.addElement<UI_ELEMENTS::BUTTON>(
      new Button("Restart",player,&MusicPlayer::restart,&MusicPlayer::restart,"",""));

  ui.addElement<UI_ELEMENTS::BUTTON>(
      new Button("Stop",player,&MusicPlayer::stop,&MusicPlayer::stop,"",""));

  ui.addElement<UI_ELEMENTS::VALUE_DISPLAY>(
      new ValueField("Time",player,&MusicPlayer::getTime));

  player.openFile("demo.wav");

  ui.run();

  return EXIT_SUCCESS;
}