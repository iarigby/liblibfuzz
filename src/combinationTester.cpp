#include "combinationTester.h"

// template <typename T> using InstanceFunctionPointer = T (*)(int);

// TODO
extern bool started;

template <typename T>
CombinationTester<T>::CombinationTester(int permutationSize,
                                        FunctionPointerMap<T> fpm,
                                        InstanceFunctionPointer<T> ifp,
                                        CoverageReporter *cr)
    : functionPointerMap{fpm}, permutationSize{permutationSize},
      getNewInstance{ifp}, coverageReporter{cr} {
  std::vector<std::string> v{fpm.getFunctions()};
  permutationGenerator = PermutationGenerator<std::string>(v, permutationSize);
}

template <typename T> void CombinationTester<T>::run() {
  while (!permutationGenerator.isDone()) {
    auto permutation = permutationGenerator.nextPermutation();
    T instance = getNewInstance(permutationSize);
    started = true;
    coverageReporter->startCoverage(permutation);
    /**
     * entire loop is wrapped in try catch so that no more functions are called
     * after an exception
     * in this implementation this step is not essential since paths are
     * explored in increasing order. So only last call could possibly cause an
     * exception However, if the implementation of permutationGenerator is
     * changed later, this guarantee will no longer hold so having the entire
     * loop wrapped in try catch will ensure that testing stops on first
     * exception
     */
    // TODO go over this explanation again
    try {
      for (auto const &functionName : permutation) {
        functionPointerMap.template searchAndCall<void>(instance, functionName);
      }
    } catch (...) {
      permutationGenerator.blacklistPermutation();
    }
    coverageReporter->flush();
    started = false;
  }
}
