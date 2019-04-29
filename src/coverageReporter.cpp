#include "coverageReporter.h"

void CoverageReporter::startCoverage(std::vector<std::string> functionSequence) {
  // TODO should I check whether the functionSequence has been covered already?
  currentSequence = functionSequence;
}

void CoverageReporter::addPCForCombination(const std::string &pc) {
  currentPC.insert(pc);
}

void CoverageReporter::flush() {
  if (currentSequence.empty()) {
    throw "no function sequence provided";
  }
  // go through the set and remove all that are smaller and
  // contain the same elments
  // TODO this is trash, rewrite
  bool isNewCoverage = true;
  auto p = coverageSequences.find(currentPC);
  if (p != coverageSequences.end()) {
    isNewCoverage = false;
    auto sequence = p->second;
    if (sequence.size() > currentSequence.size()) {
      p->second = currentSequence;
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
    coverageSequences.insert(std::make_pair(currentPC, currentSequence));
  }
  currentSequence.clear();
  currentPC.clear();
}

std::set<pc_set> CoverageReporter::coverage() {
  std::set<std::set<std::string>> s;
  for (auto const &elem : coverageSequences) {
    s.insert(elem.first);
  }
  return s;
}

bool CoverageReporter::isSubsetOf(std::set<std::string> &s1,
                                  std::set<std::string> &s2) {
  return s1.size() < s2.size() &&
         std::includes(s2.begin(), s2.end(), s1.begin(), s1.end());
  // The includes() algorithm compares two sorted sequences
         // returns true if every element in the range [start2, finish2) is
         // contained in the range [start1, finish1)
}

void CoverageReporter::writeResults(std::ostream& outstream) {
  for (const auto &coverage : coverageSequences) {
    outstream << "combination: ";
    for (const auto &func : coverage.second) {
      outstream << func << " ";
    }
    outstream << "\n";
    for (const auto &pc : coverage.first) {
      outstream << "\t" << pc << "\n";
    }
  }
}

void CoverageReporter::printResults() {
  writeResults(std::cout);
}

void CoverageReporter::printResultsToFile() {
  printResultsToFile("results.txt");
}

void CoverageReporter::printResultsToFile(std::string fileName) {
  std::ofstream outputFile;
  outputFile.open(fileName);
  writeResults(outputFile);
  outputFile.close();
}
