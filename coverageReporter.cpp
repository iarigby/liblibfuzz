#include "coverageReporter.h"

void CoverageReporter::addPCForCombination(std::string pc) {
  currentPC.insert(pc);
}

void CoverageReporter::flush() {
  // go through the set and remove all that are smaller and
  // contain the same elments
  bool isNewCoverage = true;
  for (auto it = coverage.begin(); it != coverage.end();) {
    auto s = *it;
    if (isSubsetOf(currentPC, s)) {
      isNewCoverage = false;
      break;
    }
    if (isSubsetOf(s, currentPC)) {
      isNewCoverage = true;
      it = coverage.erase(it);
    } else {
      ++it;
    }
  }
  // insert the current set
  if (isNewCoverage) {
    coverage.insert(currentPC);
  }
  currentPC.clear();
}

bool CoverageReporter::isSubsetOf(std::set<std::string> &s1,
                                  std::set<std::string> &s2) {
  return s1.size() < s2.size() &&
         // The includes() algorithm compares two sorted sequences
         // returns true if every element in the range [start2, finish2) is
         // contained in the range [start1, finish1)
         std::includes(s2.begin(), s2.end(), s1.begin(), s1.end());
}
