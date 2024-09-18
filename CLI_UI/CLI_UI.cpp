#include "CLI_UI.h"
#include <thread>

void clear() {
#if defined _WIN32
  system("cls");
    //clrscr(); // including header file : conio.h
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
  //system("clear");
  std::cout << "\033[2J\033[1;1H"; //Using ANSI Escape Sequences
#elif defined (__APPLE__)
  system("clear");
#endif
}

void CLI_UI::enableRawMode() {
  tcgetattr(STDIN_FILENO, &orig_termios);
  struct termios raw = orig_termios;
  raw.c_lflag &= ~(ECHO | ICANON);
  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 1;
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void CLI_UI::disableRawMode() {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void CLI_UI::run() {
  enableRawMode();
  while (not quit) {
    processInput();
    update();
  }
  disableRawMode();
}

void CLI_UI::update() {
  using std::cout;
  clear();
  for (size_t i = 0; i < drawOrder.size(); ++i) {
    auto[type,index] = drawOrder[i];
    switch (type) {
      case UI_ELEMENTS::BAR_GRAPH:barGraphs.at(index)->update();
        cout << *(ElementBase*)barGraphs.at(index).get();
        break;
      case UI_ELEMENTS::BUTTON:cout << *(ElementBase*)buttons.at(index).get();
        break;
      case UI_ELEMENTS::FIELD:fields.at(index)->update();
        cout << *(ElementBase*)fields.at(index).get();
        break;
    }
    if(i == selectedElement)cout << " <-";
    cout << '\n';
  }
  cout << std::endl;
}

void CLI_UI::processInput() {
  char c;
  while (read(STDIN_FILENO, &c, 1) != 0) {
    //quit
    if(c == 'q')quit = true;
    if(c == 10)enter();
    //process special keys
    if(c == '['){
      char nextC = '\0';
      read(STDIN_FILENO,&nextC,1);
      switch (nextC) {
        case 'A':
          --selectedElement;
          break;
        case 'B':
          ++selectedElement;
          break;
        default:
          break;
      }
      selectedElement %= drawOrder.size();
    }
  }
}

void CLI_UI::enter() {
  auto[type,index] = drawOrder.at(selectedElement);
  switch (type) {
    case UI_ELEMENTS::BAR_GRAPH:
      break;
    case UI_ELEMENTS::BUTTON:buttons.at(index)->toggle();
      break;
    case UI_ELEMENTS::FIELD:
      break;
  }
}

CLI_UI::~CLI_UI() {
  for(auto& ptr : fields){
    delete ptr.get();
  }
  for(auto& ptr : buttons){
    delete ptr.get();
  }
  for(auto& ptr : barGraphs){
    delete ptr.get();
  }
}
