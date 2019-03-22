#define CATCH_CONFIG_MAIN
#include "permutationGenerator.cpp"
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
  PermutationGenerator<std::string> cb(vec, 3);
  GIVEN("permuataion generator") {
    cb.nextPermutation(); // returns a
    cb.nextPermutation(); // returns a a
    WHEN("path is blacklisted") {
      cb.blacklistPermutation(); //
      THEN("no more permutations should be generated") {
        std::vector<std::string> expected{"a", "b"};
        REQUIRE(cb.nextPermutation() == expected);
      }
    }
  }
}
