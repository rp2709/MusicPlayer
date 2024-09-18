#ifndef MUSICPLAYER_CLI_UI_BARGRAPH_H_
#define MUSICPLAYER_CLI_UI_BARGRAPH_H_

#include <vector>
#include <ostream>
#include <algorithm>

#include "Types.h"

class BarGraphBase : public ElementBase {
 public:
  virtual void update() = 0;
};

template<class C>
class BarGraph : public BarGraphBase {
  using ValueType = Real;
  using Values = std::vector<ValueType>;
  unsigned maxHeight; // in character
  char full;
  char empty;
  Values values;

  C &object;
  using Method = Values(C::*)();
  Method updateGetter;
 public:
  explicit BarGraph(C &object, Method updateGetter, unsigned maxHeigth = 10, char full = '#', char empty = ' ');
  std::string print() const override;
  void update() override;
};

template<class C>
std::string BarGraph<C>::print()const {
  std::stringstream out;

  Real maxValue = *std::max_element(values.begin(), values.end());
  Real ratio = maxHeight / maxValue;

  //line
  for (unsigned h = maxHeight; h > 0; --h) {
    //column
    for (Real value : values) {
      out << (value * ratio >= h ? full : empty);
    }
    out << '\n';
  }

  return out.str();
}

template<class C>
BarGraph<C>::BarGraph(C &object, Method updateGetter, unsigned maxHeigth, char full, char empty) :
    object(object),
    maxHeight(maxHeigth),
    full(full),
    empty(empty),
    updateGetter(updateGetter) {}

template<class C>
void BarGraph<C>::update() {
  values = (object.*updateGetter)();
}

#endif //MUSICPLAYER_CLI_UI_BARGRAPH_H_
