#ifndef MUSICPLAYER_CLI_UI_VALUEFIELD_H_
#define MUSICPLAYER_CLI_UI_VALUEFIELD_H_

#include "Types.h"
#include <string>
#include <ostream>

template<typename T = Real>
class ValueField {
  T value;
  std::string name;
  std::string unit;

  UpdateDataGetter<T> updateGetter;
 public:
  explicit ValueField(std::string name, UpdateDataGetter<T> updateGetter,std::string unit = "", T initialValue = T(0));
  void update();
  template<typename VT>
  friend std::ostream& operator << (std::ostream & out, const ValueField<VT>& valueField);
};

template<typename T>
std::ostream &operator<<(std::ostream &out, const ValueField<T> &valueField) {
  out << valueField.name << " : " << valueField.value << '[' << valueField.unit << ']';
  return out;
}

template<typename T>
void ValueField<T>::update() {
  value = updateGetter();
}

template<typename T>
ValueField<T>::ValueField(std::string name,UpdateDataGetter<T> updateGetter, std::string unit, T initialValue):
name(std::move(name)),
unit(std::move(unit)),
value(initialValue),
updateGetter(updateGetter)
{}

#endif //MUSICPLAYER_CLI_UI_VALUEFIELD_H_
