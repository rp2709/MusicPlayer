#ifndef MUSICPLAYER_CLI_UI_TYPES_H_
#define MUSICPLAYER_CLI_UI_TYPES_H_

#include <string>
#include <memory>
#include <sstream>

using Real = double;

template<typename T>
using UpdateDataGetter = T(*)();

class ElementBase{
 public:
  virtual ~ElementBase() = default;
  [[nodiscard]]virtual std::string print()const = 0;
};

std::ostream& operator << (std::ostream& out, const ElementBase& element);

#endif //MUSICPLAYER_CLI_UI_TYPES_H_
