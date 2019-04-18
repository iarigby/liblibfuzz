/*******************************************************************************
 *                                main.cc                                      *
 *******************************************************************************
 * This file should be implemented by the user
 * It's divided into sections along with lines of code
 * Example code tests the stack class of type int
 */

/* HEADERS
 * libraries needed for running
 */

// replace this line with the header of your own class
#include "../examples/stack.h"
// program
#include "combinationTester.cpp"
#include "functionPointerMap.hpp"
#include <iostream>

/* GLOBALS
 */
// used by sanitizer coverage to record covered pc blocks
CoverageReporter coverageReporter;
//
bool started;

// verbose
// TODO maybe this should be a compiler flag?
bool outputMessages = false;

// extern int i;

int main(int argc, char **argv) {
  /* Function pointers
   */
  FunctionPointerMap<stack<int>> a1;
  a1.insert("pop", &stack<int>::pop);
  a1.insert("peek", &stack<int>::peek);
  a1.insert("size", &stack<int>::size);
  a1.insert("isEmpty", &stack<int>::isEmpty);
  a1.insert("isFull", &stack<int>::isFull);
  // Functions which take arguments are supported through function pointers
  // You can define them separately or pass as lambda functions
  // TODO change name to something else, now it's more confusing
  a1.insertNonVoid("push", [](stack<int> &a) { a.push(1); });

  /* Function that does all the initialization
   */
  InstanceFunctionPointer<stack<int>> getStackInstance = [](int size) {
    stack<int> s(size);
    // s.toggleOutput(true);
    return s;
  };
  /* main commands
   */
  CombinationTester<stack<int>> combinationTester(3, a1, getStackInstance,
						  &coverageReporter);
  combinationTester.run();
  coverageReporter.printResults();
  // cr.printResultsToFile();
  // comment this line if not compiling with guards
  // std::cout << i;
  std::cout << "done\n";
  return 0;
}
