#include "CLI_Interface.h"

#include <stdexcept>
#include <algorithm>
#include <iostream>

int CLI_Interface::instances = 0;

CLI_Interface::CLI_Interface() {
  if (instances != 0)
    throw std::logic_error("Cannot create multiple instances of CLI_Interface");
  ++instances;
}

void CLI_Interface::run() {
  while(true){
    std::cout << "MusicPlayer > ";
    std::string userInput; std::cin >> userInput;
    std::cout << std::endl;

    size_t argSepIndex = userInput.find_first_of('/');
    std::string arg;
    if(argSepIndex != std::string::npos){
      arg = userInput.substr(argSepIndex + 1);
      userInput = userInput.substr(0,argSepIndex);
    }

    auto commandIT = std::find(COMMANDS.begin(), COMMANDS.end(),userInput);
    if(commandIT == COMMANDS.end()){
      std::cout << "Invalid command \"" << userInput << "\". Type help for assistance" << std::endl;
      continue;
    }

    auto command = (CommandId)std::distance(COMMANDS.begin(),commandIT);

    switch (command) {
      case CommandId::exit:return;
      case CommandId::help:help();break;
      case CommandId::play:player.play();break;
      case CommandId::pause:player.pause();break;
      case CommandId::stop:player.stop();break;
      case CommandId::restart:player.restart();break;
      case CommandId::Time:std::cout << player.getTime() << std::endl;break;
      case CommandId::open:open(arg);break;
      case CommandId::setTime:player.setTime(atof(arg.data()));break;
    }
  }
}

void CLI_Interface::help() {
  std::cout << "-----MusicPlayer's help page-----\n"
            << "When seeing 'MusicPlayer >' enter one of the following commands :\n"
            << "|";
  for(auto cmd : COMMANDS){
    std::cout << cmd << "|";
  }
  std::cout << "\n----------------end---------------" << std::endl;
}

void CLI_Interface::open(const std::string& filePath) {
  try{
    player.openFile(filePath);
  }catch(std::runtime_error& error){
    std::cerr << "An error occurred while opening the file : "
              << error.what()
              << std::endl;
  }
}
