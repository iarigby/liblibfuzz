#ifndef COVERAGEREPORTER_H
#define COVERAGEREPORTER_H

#include <algorithm> // for includes()
#include <map>
#include <set>
#include <string>
#include <vector>

using pc_set = std::set<std::string>;

/**
 * Stores reported coverage
 */
class CoverageReporter {
public:
  /**
   * saves passed sequence as current one
   * \param functionSequence sequence of function names for which the coverage
   * should be recorded
   */
  void startCoverage(std::vector<std::string> functionSequence);
  /**
   * \param pc will be added to the current set of collected pcs
   */
  void addPCForCombination(const std::string &pc);
  // TODO is having a reference ok? revisit this when using
  /**
   * saves current permutation and associated coverage and empties both.
   * if exact same coverage has been found with same or shorter sequence,
   * the coverageSequences won't be updated, if longer one, the sequence for
   * coverage will be replaced.
   * otherwise, the function will check if new coverage contains any
   * of the existing ones as a subset, in which case the old coverage will
   * be removed and replaced with the larger set.
   */
  void flush();
  /**
   * get all sets coverered so far
   * \return keys of coverageSequences, set of sets
   */
  std::set<pc_set> coverage();
  /**
   *  set of all coverage points collected for current permutation
   */
  pc_set currentPC;
  /**
   * stores the shortest recorded function sequence for given coverage
   */
  std::map<pc_set, std::vector<std::string>> coverageSequences;
  // private:
  /**
   * \return if first set is subset of the second
   */
  bool isSubsetOf(pc_set &s1, pc_set &s2);
  /**
   *  which sequence the current coverage will be mapped to
   */
  std::vector<std::string> currentSequence;
};

#endif // COVERAGEREPORTER_H
