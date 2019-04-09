#include "combinationTester.cpp"
#include "functionPointerMap.hpp"
#include "../examples/stack.h"
#include <iostream>

CoverageReporter cr;
bool started;

bool outputMessages = true;

int main(int argc, char **argv) {
  FunctionPointerMap<stack<int>> a1;
  // a1.insert("push", &stack<int>::push);
  // TODO explain the design decisions in more detail
  a1.insertNonVoid("push", [](stack<int> &a) { a.push(1); });
  a1.insert("pop", &stack<int>::pop);
  a1.insert("peek", &stack<int>::peek);
  a1.insert("size", &stack<int>::size);
  a1.insert("isEmpty", &stack<int>::isEmpty);
  a1.insert("isFull", &stack<int>::isFull);
  InstanceFunctionPointer<stack<int>> getStackInstance = [](int size) {
    stack<int> s(size);
    // s.toggleOutput(true);
    return s;
  };
  CombinationTester<stack<int>> ct(3, a1, getStackInstance, &cr);
  ct.run();
  // TODO
  //  std::cout << cr.coverage() << std::endl;
  std::cout << "done\n";
}
