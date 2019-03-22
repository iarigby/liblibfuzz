#include "combinationGenerator.cpp"
#include "coverageReporter.h"
#include "functionPointerMap.cpp"
#include "stack.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>

CoverageReporter cr;
bool started;

// trace-pc-guard-example.cc

bool outputMessages = true;

int main(int argc, char **argv) {
  FunctionPointerMap<stack<int>> a1;
  // a1.insert("push", &stack<int>::push);
  a1.insertNonVoid("push", [](stack<int> &a) { a.push(1); });
  a1.insert("pop", &stack<int>::pop);
  a1.insert("peek", &stack<int>::peek);
  a1.insert("size", &stack<int>::size);
  a1.insert("isEmpty", &stack<int>::isEmpty);
  a1.insert("isFull", &stack<int>::isFull);

  // FunctionPointerMap<stack> a1;
  // a1.insert("push", &stack::push);
  // a1.insert("pop", &stack::pop);
  // a1.insert("peek", &stack::peek);
  // a1.insert("size", &stack::size);
  // a1.insert("isEmpty", &stack::isEmpty);
  // a1.insert("isFull", &stack::isFull);
  std::vector<std::string> v = {"push", "pop",     "peek",
                                "size", "isEmpty", "isFull"};
  const int combinationSize = 3;
  CombinationGenerator<std::string> cb(v, combinationSize);
  while (!cb.isDone()) {
    auto perm = cb.nextCombination();
    stack<int> s(combinationSize);
    s.toggleOutput(false);
    if (outputMessages) {
      std::cout << "***** perm";
      for (auto const &elem : perm) {
        std::cout << " " << elem;
      }
      std::cout << "\n";
    }
    started = true;
    cr.startCoverage(perm);
    try {
      for (auto const &elem : perm) {
        a1.searchAndCall<void>(s, elem);
      }
    } catch (const char *c) {
      if (outputMessages) {
        std::cout << ">> exception " << c << std::endl;
      }
      // log somewhere
    } catch (int exit_status) {
      // program terminated with status _
    } catch (...) {
      //
      std::cout << ">> exception ";
    }
    cr.flush();
    started = false;
  }
  std::cout << "done\n";
}
