#include "Types.h"

std::ostream& operator << (std::ostream& out, const ElementBase& element){
  return out << element.print();
}