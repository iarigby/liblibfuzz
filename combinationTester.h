#ifndef COMBINATIONTESTER_H
#define COMBINATIONTESTER_H

#include "combinationGenerator.h"
#include "coverageReporter.h"
#include "functionPointerMap.cpp"

#include <string>

template <typename T> using InstanceFunctionPointer = T (*)(int);

template <typename T> class CombinationTester {
public:
  CombinationTester(int combinationSize, FunctionPointerMap<T> fpm,
                    InstanceFunctionPointer<T> ifp, CoverageReporter* cr);
  void run();

private:
  int combinationSize;
  InstanceFunctionPointer<T> getNewInstance;
  CoverageReporter* coverageReporter;
  FunctionPointerMap<T> functionPointerMap;
  CombinationGenerator<std::string> combinationGenerator;
};

#endif // COMBINATIONTESTER_H
