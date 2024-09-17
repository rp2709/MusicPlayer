#ifndef MUSICPLAYER_CLI_UI_BARGRAPH_H_
#define MUSICPLAYER_CLI_UI_BARGRAPH_H_

#include <vector>
#include <ostream>
#include "Types.h"

class BarGraph {
  unsigned maxHeight; // in character
  char full;
  char empty;
  std::vector<Real> values;

  UpdateDataGetter<std::vector<Real>> updateGetter{};
 public:
  explicit BarGraph(UpdateDataGetter<std::vector<Real>> updateGetter, unsigned maxHeigth = 10, char full = '#', char empty = ' ');
  friend std::ostream& operator << (std::ostream& out, const BarGraph& barGraph);
  void update();
};

#endif //MUSICPLAYER_CLI_UI_BARGRAPH_H_
