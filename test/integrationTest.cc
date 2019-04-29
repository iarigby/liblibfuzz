#include <catch2/catch.hpp>
#include "coverageReporter.h"
#include "integrationTestClass.h"

/* GLOBALS
 */
// used by sanitizer coverage to record covered pc blocks
CoverageReporter coverageReporter;
//
bool started;

// verbose
// TODO maybe this should be a compiler flag?
bool outputMessages = false;


SCENARIO("integration test", "[integrationtest]") {
  GIVEN("abc") {
    WHEN("a") {
      IntegrationTestClass testClass;
      testClass.f1();
      THEN("b") {
      }
    }
  }
}
