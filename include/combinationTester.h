#ifndef COMBINATIONTESTER_H
#define COMBINATIONTESTER_H

#include "permutationGenerator.h"
#include "coverageReporter.h"
#include "functionPointerMap.hpp"

#include <string>

template <typename T> using InstanceFunctionPointer = T (*)(int);

/**
 * This is the class that connects all others and achieves the main task of 
// TODO sample code would be the main.cpp file
 */
template <typename T> class CombinationTester {
public:
  CombinationTester(int combinationSize, FunctionPointerMap<T> fpm,
                    InstanceFunctionPointer<T> ifp, CoverageReporter* cr);
  void run();

private:
  int permutationSize;
  /**
   * This is a user defined function that is used on each iteration
   */
  InstanceFunctionPointer<T> getNewInstance;
  CoverageReporter* coverageReporter;
  FunctionPointerMap<T> functionPointerMap;
  PermutationGenerator<std::string> permutationGenerator;
};

#endif // COMBINATIONTESTER_H
