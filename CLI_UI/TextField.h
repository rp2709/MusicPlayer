#ifndef MUSICPLAYER_CLI_UI_TEXTFIELD_H_
#define MUSICPLAYER_CLI_UI_TEXTFIELD_H_

#include "Types.h"
#include <iostream>

class TextFieldBase : public ElementBase {
 public:
  virtual void getInput() const = 0;
};

template<class C>
class TextField : public TextFieldBase {
  std::string name;
  std::string prompt;

  C &object;
  using Method = void (C::*)(const std::string &);
  Method inputUsage;
 public:
  TextField(std::string name, std::string prompt, C &object, Method inputUsage);
  std::string print() const override;
  void getInput() const override;
};

template<class C>
TextField<C>::TextField(std::string name, std::string prompt, C &object, TextField::Method inputUsage):
    name(std::move(name)),
    prompt(std::move(prompt)),
    object(object),
    inputUsage(inputUsage) {}

template<class C>
void TextField<C>::getInput() const {
  std::string text;
  std::cout << prompt << std::endl;
  char c;
  do {
    if (read(STDIN_FILENO, &c, 1) > 0){
      text.push_back(c);
      write(STDOUT_FILENO,&c,1);
    }
  } while (c != '\n');
  (object.*inputUsage)(text);
}

template<class C>
std::string TextField<C>::print() const {
  return '>' + name;
}

#endif //MUSICPLAYER_CLI_UI_TEXTFIELD_H_
