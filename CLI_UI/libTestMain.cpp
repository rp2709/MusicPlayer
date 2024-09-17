#include "CLI_UI.h"

void f1(){

}

void f2(){

}

Real getTime(){
  static Real i = 0;
  return i += 0.1;
}

std::vector<Real> getdata(){
  static std::vector<Real> data{13,45,23,8,35,10,15,25,40,39,25,15,5,0,5};
  return data;
}

int main(){
  CLI_UI ui;

  ui.addElement<UI_ELEMENTS::BUTTON>("Power",&f1,&f2);
  ui.addElement<UI_ELEMENTS::FIELD>("Time",&getTime,"s");
  ui.addElement<UI_ELEMENTS::BAR_GRAPH>(&getdata);

  ui.run();

  return 0;
}
