#ifndef COVERAGEREPORTER_H
#define COVERAGEREPORTER_H

#include <set>
#include <string>
#include <algorithm> // for includes()
#include <vector>
#include <map>

using pc_set = std::set<std::string>;

class CoverageReporter {
 public:
  void addPCForCombination(std::string pc);
  void flush();
  void startCoverage(std::vector<std::string> combination);
  auto coverage();
  pc_set currentPC;
  std::map<pc_set, std::vector<std::string>> coverageSequences; 
 private:
  bool isSubsetOf(pc_set& s1, pc_set& s2);
  std::vector<std::string> currentCombination;
};

#endif //COVERAGEREPORTER_H
