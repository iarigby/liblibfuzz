#ifndef COMBINATIONGENERATOR_H
#define COMBINATIONGENERATOR_H

#include <vector>

template <typename T> class CombinationGenerator {
public:
  CombinationGenerator(std::vector<T> is, int maxLength);
  std::vector<T> nextCombination();
  bool isDone();

private:
  std::vector<T> initialSet;
  std::vector<int> combinations;
  int setSize;
  int maxLength;
  int counter;
  int numCombinations = 0;
  int currentIndex = 0;
};

#endif // COMBINATIONGENERATOR_H