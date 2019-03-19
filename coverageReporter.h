#ifndef COVERAGEREPORTER_H
#define COVERAGEREPORTER_H

#include <set>
#include <string>
#include <algorithm> // for includes()

using pc_set = std::set<std::string>;

class CoverageReporter {
 public:
  void addPCForCombination(std::string pc);
  void flush();
  pc_set currentPC;
  std::set<pc_set> coverage;
 private:
  bool isSubsetOf(pc_set& s1, pc_set& s2);
};

#endif //COVERAGEREPORTER_H
