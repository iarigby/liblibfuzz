#include "combinationTester.hpp"
#include "coverageReporter.h"
#include "functionPointerMap.hpp"
#include "integrationTestClass.h"
#include <catch2/catch.hpp>

CoverageReporter coverageReporter;
bool started;
bool outputMessages = false;

SCENARIO("integration test", "[integrationtest]") {
  GIVEN("abc") {
    FunctionPointerMap<IntegrationTestClass> a1;
    a1.insert("increaseCounter", &IntegrationTestClass::increaseCounter);
    a1.insert("f2", &IntegrationTestClass::f2);
    a1.insertNonVoid("toggleTrue",
                     [](IntegrationTestClass &s) { s.setToggle(true); });
    a1.insertNonVoid("toggleFalse",
                     [](IntegrationTestClass &s) { s.setToggle(false); });

    InstanceFunctionPointer<IntegrationTestClass> getTestClassInstance =
        [](int size) {
          IntegrationTestClass s;
          // s.toggleOutput(true);
          return s;
        };
    CombinationTester<IntegrationTestClass> combinationTester(
        5, a1, getTestClassInstance, &coverageReporter);

    WHEN("a") {
      combinationTester.run();
      coverageReporter.printResults();
      THEN("b") {
        int increaseCounterOccurences = 0;
        // REQUIRE(increaseCounterOccurences == 2);
      }
    }
  }
}
