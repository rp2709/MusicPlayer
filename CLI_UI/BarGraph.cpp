#include "BarGraph.h"
#include <algorithm>


std::ostream &operator<<(std::ostream &out, const BarGraph &barGraph) {

  Real maxValue = *std::max_element(barGraph.values.begin(), barGraph.values.end());
  Real ratio = barGraph.maxHeight / maxValue;

  //line
  for(unsigned h = barGraph.maxHeight; h > 0; --h){
    //column
    for(Real value : barGraph.values){
      out << (value * ratio >= h ? barGraph.full : barGraph.empty);
    }
    out << '\n';
  }

  return out;
}

BarGraph::BarGraph(UpdateDataGetter<std::vector<Real>> updateGetter, unsigned maxHeigth, char full, char empty) :
maxHeight(maxHeigth),
full(full),
empty(empty),
updateGetter(updateGetter)
{}

void BarGraph::update() {
  values = updateGetter();
}