#include "interfaceWithInput.h"

int InterfaceWithInput::function1(int a) { return a; }
int InterfaceWithInput::function2(int b) { return function3(b); }
int InterfaceWithInput::function3(int c) {
  if (c > 15) {
    return function2(c);
  } else if (c > 3) {
    int a = function4(c);
    if (a < 5) {
      return function3(-5);
    }
  } else {
    return 3;
  }
}
int InterfaceWithInput::function5(int e) {
  if (e % 3 == 0) {
    return function4(e);
  } else {
    return 3;
  }
}
int InterfaceWithInput::function4(int d) { return d * 5; }
