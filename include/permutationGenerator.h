#ifndef PERMUTATIONGENERATOR_H
#define PERMUTATIONGENERATOR_H

#include <vector>

/**
 * responsible for generating all possible length sequence permutations.
 * Example:  for a set for {"a", "b"}, with maxLength 2 it will generate {"a"}, {"a", "a"} ..
 * {"b"}, {"b", "a"} .. {"b", "b"}, etc
 */
// TODO explain differences from std permutation
template <typename T> class PermutationGenerator {
public:
  /**
   * creates a new permutation generator.
   * \param is will be used to select elements for sequence permutations
   * \param maxLenght is a limit for maximum sequence length
   */
  // TODO change vector to a set (and explain why it is used)
  PermutationGenerator(std::vector<T> is, int maxLength);
  PermutationGenerator();
  /**
   * \return the next permutation
   * The permutation selection order follows inorder traversal of the tree. It
   * will start out with a first element of the set
   *
   */
  std::vector<T> nextPermutation();
  /**
   * \return whether all possible permutations of all length have been returned
   * previosly
   */
  bool isDone(); // TODO maybe better if this class will be a container (using
                 // iterator with ++ and end() makes sense)
  /**
   * will blacklist all sequences that start with the sequence last generated.
   * Ie stop exploring the path
   */
  void blacklistPermutation();

private:
  /**
   * elements of the sequences that will be returned */
  std::vector<T> initialSet;
  /**
   * this is the vector that is actually permuted. Stored elements are indices
   * of the initialSet */
  std::vector<int> permutations;
  /**
   * maximum value that element in permutations can take */
  int setSize;
  int maxLength;
  int counter;
  /**
   * which element in permutations should be incremented next */
  int currentIndex = 0;
  /**
   * saves last index so it can blacklist the last generated path */
  int lastIndex = 0;
};

#endif // PERMUTATIONGENERATOR_H
