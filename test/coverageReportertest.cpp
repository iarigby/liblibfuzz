#define CATCH_CONFIG_MAIN

#include "coverageReporter.h"
#include <catch2/catch.hpp>

struct TestData {
  std::vector<std::string> shortCombination{"f1"};
  std::vector<std::string> combination1{"f1", "f2"};
  std::vector<std::string> combination2{"f2", "f3"};
  std::vector<std::string> longCombination{"f1", "f2", "f3"};
};

using pc_set = std::set<std::string>;
SCENARIO("coverage reporting", "[coveragereporter]") {
  TestData testData;
  CoverageReporter cr;
  const pc_set smallCoverage = {"pc1"};
  const pc_set largeCoverage = {"pc1", "pc2"};
  GIVEN("coverage reporter with no coverage") {
    cr.startCoverage(testData.combination1);
    WHEN("flush is called") {
      cr.addPCForCombination("pc1");
      REQUIRE(cr.currentPC == smallCoverage);
      cr.flush();
      THEN("currentPC should be inserted to coverage and cleared") {
        std::set<pc_set> expectedCoverage{{"pc1"}};
        REQUIRE(cr.coverage() == expectedCoverage);
        REQUIRE(cr.currentPC.empty());
      }
    }
  }
  
  GIVEN("new coverage") {
    cr.startCoverage(testData.combination1);
    WHEN("exists coverage that is a subset of new reporting") {
      cr.addPCForCombination("pc1");
      cr.flush();
      cr.startCoverage(testData.shortCombination);
      cr.addPCForCombination("pc2");
      cr.flush();
      cr.startCoverage(testData.combination2);
      cr.addPCForCombination("pc1");
      cr.addPCForCombination("pc2");
      REQUIRE(cr.currentPC == largeCoverage);
      cr.flush();
      THEN("all of them should be removed") {
        std::set<pc_set> expectedCoverage{largeCoverage};
        REQUIRE(cr.coverage() == expectedCoverage);
	REQUIRE(cr.coverageSequences.size() == 1);
      }
    }

    WHEN("new coverage is not contained in one of the sets") {
      cr.addPCForCombination("pc1");
      cr.addPCForCombination("pc2");
      cr.flush();
      cr.startCoverage(testData.combination2);
      cr.addPCForCombination("pc3");
      cr.flush();
      THEN("new coverage should be inserted") {
        std::set<pc_set> expectedCoverage{{"pc3"}, largeCoverage};
        REQUIRE(cr.coverage() == expectedCoverage);
      }
    }
    WHEN("new coverage is already contained in one of the sets") {
      cr.addPCForCombination("pc1");
      cr.addPCForCombination("pc2");
      cr.flush();
      cr.startCoverage(testData.combination2);
      cr.addPCForCombination("pc2");
      cr.flush();
      THEN("new coverage should not be inserted") {
        std::set<pc_set> expectedCoverage{largeCoverage};
        REQUIRE(cr.coverage() == expectedCoverage);
      }
    }
  }
}

SCENARIO("new combination already exists in the set") {
  TestData testData;
  CoverageReporter cr;
  cr.startCoverage(testData.combination1);
  pc_set coverage = {"pc1", "pc2"};
  cr.addPCForCombination("pc1");
  cr.addPCForCombination("pc2");
  cr.flush();
  auto sequence = cr.coverageSequences.find(coverage)->second;
  REQUIRE(sequence == testData.combination1);
  GIVEN("new coverage with sequence of same length") {
    cr.startCoverage(testData.combination2);
    cr.addPCForCombination("pc1");
    cr.addPCForCombination("pc2");
    cr.flush();
    THEN("existing sequence for coverage should not be replaced") {
      auto sequence = cr.coverageSequences.find(coverage)->second;
      REQUIRE(sequence == testData.combination1);
    }
  }

  GIVEN("new coverage with longer sequence") {
    cr.startCoverage(testData.longCombination);
    cr.addPCForCombination("pc1");
    cr.addPCForCombination("pc2");
    cr.flush();
    THEN("existing sequence for coverage should not be replaced") {
      auto sequence = cr.coverageSequences.find(coverage)->second;
      REQUIRE(sequence == testData.combination1);
    }
  }

  GIVEN("new coverage with shorter sequence") {
    cr.startCoverage(testData.shortCombination);
    cr.addPCForCombination("pc1");
    cr.addPCForCombination("pc2");
    cr.flush();
    THEN("existing sequence for coverage should be updated with new one") {
      auto sequence = cr.coverageSequences.find(coverage)->second;
      REQUIRE(sequence == testData.shortCombination);
    }
  }
}

SCENARIO("user forgot to set current combination", "[coveragereporter]") {
  CoverageReporter cr;
  std::vector<std::string> combination{"f1", "f2"};
  cr.startCoverage(combination);
  cr.addPCForCombination("pc1");
  cr.flush();
  cr.addPCForCombination("pc2");
  GIVEN("coverage reporter without current combination") {
    THEN("flushing would cause an exception") { REQUIRE_THROWS(cr.flush()); }
  }
}
