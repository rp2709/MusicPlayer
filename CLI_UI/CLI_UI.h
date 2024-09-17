#ifndef MUSICPLAYER_CLI_UI_CLI_UI_H_
#define MUSICPLAYER_CLI_UI_CLI_UI_H_

#include "BarGraph.h"
#include "Button.h"
#include "ValueField.h"
#include <vector>
#include <iostream>
#include <termios.h>
#include <unistd.h>

enum class UI_ELEMENTS { BAR_GRAPH, BUTTON, FIELD };

class CLI_UI {
  //ui elements
  std::vector<BarGraph> barGraphs;
  std::vector<Button> buttons;
  std::vector<ValueField<>> fields;

  //ui draw order
  using ElementIndex = std::pair<UI_ELEMENTS, size_t>;
  std::vector<ElementIndex> drawOrder;

  size_t selectedElement = 0;
  bool quit = false;

  //termios flags
  termios orig_termios;
  void enableRawMode();
  void disableRawMode();

  //helpers
  void update();
  void processInput();
  void enter();
 public:
  template<UI_ELEMENTS elementType,typename... Args>
  void addElement(Args&& ...args);
  void run();

};

template<UI_ELEMENTS elementType, typename... Args>
void CLI_UI::addElement(Args&& ...args) {
  size_t index;

  if constexpr (elementType == UI_ELEMENTS::BAR_GRAPH) {
    index = barGraphs.size();
    barGraphs.emplace_back(std::forward<Args>(args)...);
  } else if constexpr (elementType == UI_ELEMENTS::BUTTON) {
    index = buttons.size();
    buttons.emplace_back(std::forward<Args>(args)...);
  } else if constexpr (elementType == UI_ELEMENTS::FIELD) {
    index = fields.size();
    fields.emplace_back(std::forward<Args>(args)...);
  }

  drawOrder.emplace_back(elementType, index);
}

#endif //MUSICPLAYER_CLI_UI_CLI_UI_H_
