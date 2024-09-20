#ifndef MUSICPLAYER_CLI_UI_CLI_UI_H_
#define MUSICPLAYER_CLI_UI_CLI_UI_H_

#include "BarGraph.h"
#include "Button.h"
#include "ValueField.h"
#include "TextField.h"
#include <vector>
#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <memory>

enum class UI_ELEMENTS { BAR_GRAPH, BUTTON, VALUE_DISPLAY, TEXT_FIELD,CLI_UI_INSTANCE };

class CLI_UI : public ElementBase{
  std::string name;
  //ui elements
  std::vector<std::unique_ptr<BarGraphBase>> barGraphs;
  std::vector<std::unique_ptr<ButtonBase>> buttons;
  std::vector<std::unique_ptr<ValueFieldBase>> fields;
  std::vector<std::unique_ptr<TextFieldBase>> textFields;
  std::vector<CLI_UI*> subDir;

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
  std::string print()const override;

 public:
  explicit CLI_UI(std::string name = "");
  template<UI_ELEMENTS elementType,typename ElementPtr>
  void addElement(ElementPtr elementPtr);
  void run();

};

template<UI_ELEMENTS elementType, typename ObjectPointer>
void CLI_UI::addElement(ObjectPointer elementPtr) {
  size_t index;

  if constexpr (elementType == UI_ELEMENTS::BAR_GRAPH) {
    index = barGraphs.size();
    barGraphs.push_back(std::unique_ptr<BarGraphBase>(elementPtr));
  } else if constexpr (elementType == UI_ELEMENTS::BUTTON) {
    index = buttons.size();
    buttons.push_back(std::unique_ptr<ButtonBase>(elementPtr));
  } else if constexpr (elementType == UI_ELEMENTS::VALUE_DISPLAY) {
    index = fields.size();
    fields.push_back(std::unique_ptr<ValueFieldBase>(elementPtr));
  } else if constexpr (elementType == UI_ELEMENTS::CLI_UI_INSTANCE){
    index = subDir.size();
    subDir.push_back(elementPtr);
  } else if constexpr (elementType == UI_ELEMENTS::TEXT_FIELD){
    index = textFields.size();
    textFields.push_back(std::unique_ptr<TextFieldBase>(elementPtr));
  }

  drawOrder.emplace_back(elementType, index);
}

#endif //MUSICPLAYER_CLI_UI_CLI_UI_H_
