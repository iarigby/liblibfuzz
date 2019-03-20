#include "coverageReporter.h"

void CoverageReporter::startCoverage(std::vector<std::string> combination) {
  // TODO should I check whether the combination has been covered already?
  currentCombination = combination;
}

void CoverageReporter::addPCForCombination(const std::string &pc) {
  currentPC.insert(pc);
}

/**
 * clears current combination and recorded coverage
 * if exact same coverage has been found with same or shorter sequence,
 * the coverageSequences won't be updated, if longer one, the sequence for 
 * coverage will be replaced.
 * otherwise, the function will check if new coverage contains any 
 * of the existing ones as a subset, in which case the old coverage will
 * be removed and replaced with the larger set.
 */
void CoverageReporter::flush() {
  if (currentCombination.empty()) {
    throw "no combination provided";
  }
  // go through the set and remove all that are smaller and
  // contain the same elments
  // TODO this is trash, rewrite
  bool isNewCoverage = true;
  auto p = coverageSequences.find(currentPC);
  if (p != coverageSequences.end()) {
    isNewCoverage = false;
    auto sequence = p->second;
    if (sequence.size() > currentCombination.size()) {
      p->second = currentCombination;
    }
  }

  for (auto it = coverageSequences.begin();
       it != coverageSequences.end() && isNewCoverage;) {
    auto s = it->first;
    if (isSubsetOf(currentPC, s)) {
      isNewCoverage = false;
    }
    if (isSubsetOf(s, currentPC)) {
      it = coverageSequences.erase(it);
    } else {
      ++it;
    }
  }
  // insert the current set
  if (isNewCoverage) {
    coverageSequences.insert(std::make_pair(currentPC, currentCombination));
  }
  currentCombination.clear();
  currentPC.clear();
}

auto CoverageReporter::coverage() {
  std::set<std::set<std::string>> s;
  for (auto const &elem : coverageSequences) {
    s.insert(elem.first);
  }
  return s;
}

bool CoverageReporter::isSubsetOf(std::set<std::string> &s1,
                                  std::set<std::string> &s2) {
  return s1.size() < s2.size() &&
         // The includes() algorithm compares two sorted sequences
         // returns true if every element in the range [start2, finish2) is
         // contained in the range [start1, finish1)
         std::includes(s2.begin(), s2.end(), s1.begin(), s1.end());
}
