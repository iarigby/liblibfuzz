#include "integrationTestClass.h"

void IntegrationTestClass::f1() {
  counter++;
}

int IntegrationTestClass::f2() {
  if (toggle) {
    if (f3()) {
      return counter;
    } else {
      return 0;
    }
  } else {
    return f4();
  }
}

bool IntegrationTestClass::f3() {
  return counter > 3;
}

int IntegrationTestClass::f4() {
  return 5;
}
