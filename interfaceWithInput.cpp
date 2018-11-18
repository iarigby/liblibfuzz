#include "interfaceWithInput.h"

int InterfaceWithInput::function1(int a) { return a; }
int InterfaceWithInput::function2(int b) { return function3(b); }
int InterfaceWithInput::function3(int c) {
  int res = 3;
  if (c > 15) {
    res = function2(c);
  } else if (c > 3) {
    int a = function4(c);
    if (a < 5) {
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
