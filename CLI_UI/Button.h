#ifndef MUSICPLAYER_CLI_UI_BUTTON_H_
#define MUSICPLAYER_CLI_UI_BUTTON_H_

#include <string>
#include <ostream>

class Button {
  using Action = void (*)();
  Action onPress;
  Action onRelease;
  bool isPressed;
  std::string pressedText;
  std::string releasedText;
  std::string name;
 public:
  Button(std::string name, Action onPress, Action onRelease, std::string pressedText = "on", std::string releasedText = "off");
  void toggle();
  friend std::ostream& operator << (std::ostream& out, const Button& button);
};

#endif //MUSICPLAYER_CLI_UI_BUTTON_H_
