#include "Button.h"

Button::Button(std::string name,
               Button::Action onPress,
               Button::Action onRelease,
               std::string pressedText,
               std::string releasedText) :

               name(std::move(name)),
               onPress(onPress),
               onRelease(onRelease),
               pressedText(std::move(pressedText)),
               releasedText(std::move(releasedText)),
               isPressed(false)
               {}

void Button::toggle() {
  isPressed = not isPressed;
  if(isPressed)
    onPress();
  else
    onRelease();
}

std::ostream &operator<<(std::ostream &out, const Button &button) {

  out << button.name << '[' << (button.isPressed ? button.pressedText : button.releasedText) << ']';

  return out;
}
