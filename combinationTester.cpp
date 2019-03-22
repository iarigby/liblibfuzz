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
  // TODO
  std::vector<std::string> v{"push", "pop",     "peek",
                             "size", "isEmpty", "isFull"};
  permutationGenerator = PermutationGenerator<std::string>(v, permutationSize);
}

template <typename T> void CombinationTester<T>::run() {
  while (!permutationGenerator.isDone()) {
    auto permutation = permutationGenerator.nextPermutation();
    T instance = getNewInstance(permutationSize);
    started = true;
    coverageReporter->startCoverage(permutation);
    try {
      for (auto const &functionName : permutation) {
        // ha?
        // https://stackoverflow.com/questions/3786360/confusing-template-error
        functionPointerMap.template searchAndCall<void>(instance, functionName);
      }
    } catch (...) {
      // blacklist path
    }
    coverageReporter->flush();
    started = false;
  }
}
