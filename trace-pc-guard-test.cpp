#include "functionPointerMap.cpp"
#include "stack.h"
#include <iostream>
#include <string>
#include <vector>
// #include "stack.cpp"
// #include "stack-nontemplate.h"
#include "combinationGenerator.cpp"
#include <map>

std::map<std::vector<std::string>, std::vector<std::string>> pcCalls;
std::vector<std::string> currentPermutation;
bool started;

// trace-pc-guard-example.cc

int main(int argc, char **argv) {
  FunctionPointerMap<stack<int>> a1;
  // a1.insert("push", &stack<int>::push);
  a1.insertNonVoid("push", [](stack<int> &a) {a.push(1);});
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
  std::vector<std::string> v = {"push", "pop", "peek", "size", "isEmpty", "isFull"};
  const int combinationSize = 2;
  const bool outputMessages = true;
  CombinationGenerator<std::string> cb(v, combinationSize);
  while (!cb.isDone()) {
    auto perm = cb.nextCombination();
    currentPermutation = perm;
    std::vector<std::string> calls;
    pcCalls.insert(std::make_pair(perm, calls));
    stack<int> s(combinationSize);
    // doing this now because so stack doesn't exit after under/overflow
    // stack s(combinationSize);
    //for (int i = 0; i < combinationSize; ++i) {
    //  s.push(i);
    //}
    if (outputMessages) {
      std::cout << "***** perm";
      for (auto const &elem : perm) {
        std::cout << " " << elem;
      }
      std::cout << "\n";
    }
    started = true;
    for (auto const &elem : perm) {
      a1.searchAndCall<void>(s, elem);
    }
    started = false;
  }
  std::cout << "done\n";
}
