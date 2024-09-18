#ifndef MUSICPLAYER_CLI_UI_BUTTON_H_
#define MUSICPLAYER_CLI_UI_BUTTON_H_

#include <string>
#include <ostream>
#include <memory>

class ButtonBase : public ElementBase{
 public:
  virtual void toggle() = 0;
};

template<class C>
class Button : public ButtonBase{
  C& object;
  using Action = void(C::*)();
  Action onPress;
  Action onRelease;

  bool isPressed;
  std::string pressedText;
  std::string releasedText;
  std::string name;
 public:
  Button(std::string name, C& object,Action onPress, Action onRelease, std::string pressedText = "on", std::string releasedText = "off");
  void toggle()override;
  std::string print()const override;
};

template<class C>
std::string Button<C>::print() const{
  std::stringstream out;
  out << name << '[' << (isPressed ? pressedText : releasedText) << ']';
  return out.str();
}

template<class C>
Button<C>::Button(std::string name,
               C& object,
               Button::Action onPress,
               Button::Action onRelease,
               std::string pressedText,
               std::string releasedText) :

    name(std::move(name)),
    object(object),
    onPress(onPress),
    onRelease(onRelease),
    pressedText(std::move(pressedText)),
    releasedText(std::move(releasedText)),
    isPressed(false)
{}

template<class C>
void Button<C>::toggle() {
  isPressed = not isPressed;
  if(isPressed)
    (object.*onPress)();
  else
    (object.*onRelease)();
}

#endif //MUSICPLAYER_CLI_UI_BUTTON_H_
