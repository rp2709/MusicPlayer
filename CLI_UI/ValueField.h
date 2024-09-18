#ifndef MUSICPLAYER_CLI_UI_VALUEFIELD_H_
#define MUSICPLAYER_CLI_UI_VALUEFIELD_H_

#include "Types.h"
#include <string>
#include <ostream>

class ValueFieldBase : public ElementBase{
 public:
  virtual void update() = 0;
};

template<class C, typename T = Real>
class ValueField : public ValueFieldBase{
  T value;
  std::string name;
  std::string unit;

  using Method = T(C::*)()const;
  C& object;
  Method updateGetter;

 public:
  explicit ValueField(std::string name, C& object, Method updateGetter, std::string unit = "", T initialValue = T(0));
  void update()override;
  std::string print()const override;
};
template<class C, typename T>
std::string ValueField<C, T>::print()const {
  std::stringstream out;
  out << name << " : " << value << '[' << unit << ']';;
  return out.str();
}

template<class C,typename T>
void ValueField<C,T>::update() {
  value = (object.*updateGetter)();
}

template<class C,typename T>
ValueField<C,T>::ValueField(std::string name, C& object, Method updateGetter, std::string unit, T initialValue):
name(std::move(name)),
unit(std::move(unit)),
value(initialValue),
object(object),
updateGetter(updateGetter)
{}

#endif //MUSICPLAYER_CLI_UI_VALUEFIELD_H_
