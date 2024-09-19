#include "CLI_UI.h"

class Foo{
  int x;
 public:
  explicit Foo(int x):x(x){}
  void m1(){}
  void m2(){}
  std::vector<Real> getdata(){
    static std::vector<Real> data{13,45,23,8,35,10,15,25,40,39,25,15,5,0,5};
    return data;
  }
  Real getTime()const{
    static Real i = 0;
    return i += 0.1;
  }
};

int main(int argc, char* argv[]){
  CLI_UI ui("Main menu");
  CLI_UI sub("Sub menu");
  Foo thing(1);

  ui.addElement<UI_ELEMENTS::BUTTON>(new Button("Power",thing,&Foo::m1,&Foo::m2));
  ui.addElement<UI_ELEMENTS::FIELD>(new ValueField("Time",thing,&Foo::getTime,"s"));
  ui.addElement<UI_ELEMENTS::BAR_GRAPH>(new BarGraph(thing,&Foo::getdata));

  ui.addElement<UI_ELEMENTS::CLI_UI_INSTANCE>(&sub);

  ui.run();

  return 0;
}
