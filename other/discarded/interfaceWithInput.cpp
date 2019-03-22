#include "interfaceWithInput.h"
#include <iostream>

int InterfaceWithInput::function1(int a) { return a; }
int InterfaceWithInput::function2(int b) { return function3(b); }
int InterfaceWithInput::function3(int c) {
  int res = 3;
  if (c > 15) {
    res = function2(c);
    std::cout << "if" << std::endl; 
  } else if (c > 3) {
    std::cout << "else if";
    int a = function4(c);
    if (a < 100) {
      std::cout << "else if if" << std::endl;
      res = function3(-5);
    }
  }
  return res;
}
int InterfaceWithInput::function5(int e) {
  int res = 3;
  if (e % 3 == 0) {
    res = function4(e);
  } 
  return res;
}
int InterfaceWithInput::function4(int d) { return d * 5; }
