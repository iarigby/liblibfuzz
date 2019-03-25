#ifndef COMBINATIONTESTER_H
#define COMBINATIONTESTER_H

#include "permutationGenerator.h"
#include "coverageReporter.h"
#include "../src/functionPointerMap.cpp"

#include <string>

template <typename T> using InstanceFunctionPointer = T (*)(int);

template <typename T> class CombinationTester {
public:
  CombinationTester(int combinationSize, FunctionPointerMap<T> fpm,
                    InstanceFunctionPointer<T> ifp, CoverageReporter* cr);
  void run();

private:
  int permutationSize;
  InstanceFunctionPointer<T> getNewInstance;
  CoverageReporter* coverageReporter;
  FunctionPointerMap<T> functionPointerMap;
  PermutationGenerator<std::string> permutationGenerator;
};

#endif // COMBINATIONTESTER_H
