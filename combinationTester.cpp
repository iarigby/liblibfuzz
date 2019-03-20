#include "combinationTester.h"

// template <typename T> using InstanceFunctionPointer = T (*)(int);

template <typename T>
CombinationTester<T>::CombinationTester(int combinationSize,
                                        FunctionPointerMap<T> fpm,
                                        InstanceFunctionPointer<T> ifp)
    : functionPointerMap{fpm}, combinationSize{combinationSize},
      getNewInstance{ifp} {
  std::vector<std::string> v{"push", "pop",     "peek",
                             "size", "isEmpty", "isFull"};
  combinationGenerator = CombinationGenerator<std::string>(v, combinationSize);
}

template <typename T> void CombinationTester<T>::run() {
  while (!combinationGenerator.isDone()) {
    auto combination = combinationGenerator.nextCombination();
    T instance = getNewInstance(combinationSize);
    // started = true;
    coverageReporter.startCoverage(combination);
    try {
      for (auto const &functionName : combination) {
        // ha?
        // https://stackoverflow.com/questions/3786360/confusing-template-error
        functionPointerMap.template searchAndCall<void>(instance, functionName);
      }
    } catch (...) {
      // blacklist path
    }
    coverageReporter.flush();
    // started = false;
  }
}
