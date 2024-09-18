#ifndef MUSICPLAYER_CLI_UI_CLI_UI_H_
#define MUSICPLAYER_CLI_UI_CLI_UI_H_

#include "BarGraph.h"
#include "Button.h"
#include "ValueField.h"
#include <vector>
#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <memory>

enum class UI_ELEMENTS { BAR_GRAPH, BUTTON, FIELD };

class CLI_UI {
  //ui elements
  std::vector<std::unique_ptr<BarGraphBase>> barGraphs;
  std::vector<std::unique_ptr<ButtonBase>> buttons;
  std::vector<std::unique_ptr<ValueFieldBase>> fields;

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
  template<UI_ELEMENTS elementType,typename ObjectPointer>
  void addElement(ObjectPointer ptr);
  ~CLI_UI();
  void run();

};

template<UI_ELEMENTS elementType, typename ObjectPointer>
void CLI_UI::addElement(ObjectPointer ptr) {
  size_t index;

  if constexpr (elementType == UI_ELEMENTS::BAR_GRAPH) {
    index = barGraphs.size();
    barGraphs.push_back(std::unique_ptr<BarGraphBase>(ptr));
  } else if constexpr (elementType == UI_ELEMENTS::BUTTON) {
    index = buttons.size();
    buttons.push_back(std::unique_ptr<ButtonBase>(ptr));
  } else if constexpr (elementType == UI_ELEMENTS::FIELD) {
    index = fields.size();
    fields.push_back(std::unique_ptr<ValueFieldBase>(ptr));
  }

  drawOrder.emplace_back(elementType, index);
}

#endif //MUSICPLAYER_CLI_UI_CLI_UI_H_
