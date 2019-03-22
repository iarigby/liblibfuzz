#define CATCH_CONFIG_MAIN
#include "../include/permutationGenerator.h"
#include <catch2/catch.hpp>
#include <string>
#include <vector>

TEST_CASE("permutation generation test", "[permutationgenerator]") {
  std::vector<std::string> vec = {"a", "b"};
  PermutationGenerator<std::string> cb(vec, 3);
  std::vector<std::vector<std::string>> allPermutations;
  while (!cb.isDone()) {
    allPermutations.push_back(cb.nextPermutation());
  }
  std::vector<std::vector<std::string>> ans = {
      {"a"},           {"a", "a"},      {"a", "a", "a"}, {"a", "a", "b"},
      {"a", "b"},      {"a", "b", "a"}, {"a", "b", "b"}, {"b"},
      {"b", "a"},      {"b", "a", "a"}, {"b", "a", "b"}, {"b", "b"},
      {"b", "b", "a"}, {"b", "b", "b"},
  };
  REQUIRE(allPermutations == ans);
}

SCENARIO("path blacklisting", "[permutationgenerator]") {
  std::vector<std::string> vec = {"a", "b"};
  GIVEN("permuataion generator") {
    PermutationGenerator<std::string> cb(vec, 3);
    WHEN("path is blacklisted") {
      cb.nextPermutation();      // returns a
      cb.nextPermutation();      // returns a a
      cb.blacklistPermutation(); // skip {a, a, a} and {a, a, b}
      THEN("no more permutations starting with it should be generated") {
        std::vector<std::string> expected{"a", "b"};
        REQUIRE(cb.nextPermutation() == expected);
        cb.blacklistPermutation();
        expected = {"b"};
        REQUIRE(cb.nextPermutation() == expected);
      }
    }
    WHEN("path starting with last element is blacklisted") {
      cb.nextPermutation(); // a
      cb.blacklistPermutation(); // jump to b
      std::vector<std::string> expected{"b"};
      REQUIRE(cb.nextPermutation() == expected);
      cb.blacklistPermutation();
      THEN("generator should finish generating more") {
	REQUIRE(cb.isDone());
      }
    }
  }
}
