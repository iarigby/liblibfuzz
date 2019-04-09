#ifndef COMBINATIONTESTER_H
#define COMBINATIONTESTER_H

#include "coverageReporter.h"
#include "functionPointerMap.hpp"
#include "permutationGenerator.h"

#include <string>

template <typename T> using InstanceFunctionPointer = T (*)(int);

/**
 * This is the class that connects all others and achieves the main task of
// TODO sample code would be the main.cpp file
 */
template <typename T> class CombinationTester {
public:
  /**
   * Collects all the necessary objects
   * constructs a new permutation generator for this test run.
   * \param combinationSize maximum length of function call sequences that user
   * wants to test \param fpm see member CombinationTester#functionPointerMap
   * \param ifp see member CombinationTester#getNewInstance
   * \param cr see member CombinationTester#coverageReporter
   */
  CombinationTester(int combinationSize, FunctionPointerMap<T> fpm,
                    InstanceFunctionPointer<T> ifp, CoverageReporter *cr);
  /**
   * This function will keep getting new function sequences from permutation
   * generator until it has explored all paths.
   * On each iteration:
   *   1. New permutation of function call sequences is retrieved.
   *   2. Instance of test class is constructed using the getNewInstance
   * function pointer
   *   3. Coverage reporting is initialized with the new permutation
   *   4. Each function in the sequence is called using the functionpointermap.
   * During this step, sanitizerCoverage library functions will insert found pc
   * guards to coverageReporter. If CombinationTester encounters an exception
   * during this step, it blacklists the path, stops  and doesn't explore any
   * further paths starting with that sequence, since all possible continuations
   * would be interrupted with that exception and won't provide any new
   * meaningful coverage.
   *   5. Finally, coverageReporter is flushed
   */
  // TODO should this automatically start? what could be some actions that the
  // user might want to take
  void run();

private:
  int permutationSize;
  /**
   * User defined function that is used on each iteration for constructing a new
   * instance of test target class. Passing a function makes it easier to set up
   * the class and its dependencies easily.
   */
  InstanceFunctionPointer<T> getNewInstance;
  /**
   * pointer to a global instance of coverage reporter. We need this object to
   * be global so that when the sanitizer coverage functions are called, they
   * can access it
   */
  // TODO fix this
  CoverageReporter *coverageReporter;
  /**
   * Map consisting of pointers to all the functions that will be tested. There
   * are two types of functions you can pass pointers to:
   *    1. Member functions
   *    2. void functions taking the class instance as an argument
   */
  // TODO describe in more detail
  FunctionPointerMap<T> functionPointerMap;
  /**
   * Created using the keys of functionPointerMap and combinationSize passed in
   * the constructor
   */
  PermutationGenerator<std::string> permutationGenerator;
};

#endif // COMBINATIONTESTER_H
