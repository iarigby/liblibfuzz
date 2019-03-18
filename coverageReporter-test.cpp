#define CATCH_CONFIG_MAIN

#include "coverageReporter.cpp"
#include <catch2/catch.hpp>

using pc_set = std::set<std::string>;
SCENARIO("coverage reporting", "[coveragereporter]") {
  GIVEN("coverage reporter with existing coverage") {
    CoverageReporter cr;

    pc_set smallCoverage = {"pc1"};
    pc_set largeCoverage = {"pc1", "pc2"};
    WHEN("flush is called") {
      cr.addPCForCombination("pc1");
      REQUIRE(cr.currentPC == smallCoverage);
      cr.flush();
      THEN("currentPC should be inserted to coverage and cleared") {
        std::set<pc_set> expectedCoverage{{"pc1"}};
        REQUIRE(cr.coverage == expectedCoverage);
        REQUIRE(cr.currentPC.empty());
      }
    }

    WHEN("set in coverage is a subset of new reporting") {
      cr.addPCForCombination("pc1");
      cr.flush();
      cr.addPCForCombination("pc1");
      cr.addPCForCombination("pc2");
      REQUIRE(cr.currentPC == largeCoverage);
      cr.flush();
      THEN("it should be removed") {
        std::set<pc_set> expectedCoverage{largeCoverage};
        REQUIRE(cr.coverage == expectedCoverage);
      }
    }

    WHEN("new coverage is not contained in one of the sets") {
      cr.addPCForCombination("pc1");
      cr.addPCForCombination("pc2");
      cr.flush();
      cr.addPCForCombination("pc3");
      cr.flush();
      THEN("new coverage should be inserted") {
        std::set<pc_set> expectedCoverage{{"pc3"}, largeCoverage};
	REQUIRE(cr.coverage == expectedCoverage);
      }
    }
    WHEN("new coverage is already contained in one of the sets") {
      cr.addPCForCombination("pc1");
      cr.addPCForCombination("pc2");
      cr.flush();
      cr.addPCForCombination("pc2");
      cr.flush();
      THEN("new coverage should not be inserted") {
        std::set<pc_set> expectedCoverage{largeCoverage};
        REQUIRE(cr.coverage == expectedCoverage);
      }
    }
  }
}
