#include "permutationGenerator.h"
#include <string>

template <typename T>
PermutationGenerator<T>::PermutationGenerator() {}

template <typename T>
PermutationGenerator<T>::PermutationGenerator(std::vector<T> is, int ml)
    : initialSet(is), maxLength(ml) {
  for (int i = 0; i < ml; ++i) {
    permutations.push_back(-1);
  }
  int comb = 1;
  for (int i = 2; i < ml; ++i) {
    comb *= i;
  }
  setSize = is.size();
}

template <typename T>
std::vector<T> PermutationGenerator<T>::nextPermutation() {
  int &elem = permutations[currentIndex];
  if (elem == setSize - 1) {
    elem = -1;
    currentIndex--;
    return nextPermutation();
  } else {
    elem++;
    if (currentIndex < maxLength - 1) {
      currentIndex++;
    }
  }
  std::vector<T> res;
  for (const int &index : permutations) {
    if (index > -1)
      res.push_back(initialSet[index]);
  }
  return res;
}

template <typename T> bool PermutationGenerator<T>::isDone() {
  for (auto const &index : permutations) {
    if (index < setSize - 1) {
      return false;
    }
  }
  return true;
}

template class PermutationGenerator<std::string>;
