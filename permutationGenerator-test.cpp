#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "permutationGenerator.cpp"
#include <vector>
#include <string>

TEST_CASE("permutation generation test", "[permutationgenerator]") {
    std::vector<std::string> vec = {"a", "b"};
    PermutationGenerator<std::string> cb(vec, 3);
    std::vector<std::vector<std::string>> allPermutations;
    int i = 0;
    while (!cb.isDone() && i<100) {
        i++;
        allPermutations.push_back(cb.nextPermutation());
    }
    std::vector<std::vector<std::string>> ans = {
        {"a"}, {"a", "a"}, 
        {"a","a","a"},{"a", "a", "b"},
        {"a","b"}, 
        {"a","b","a"},{"a", "b", "b"},
        {"b"}, {"b", "a"}, 
        {"b","a","a"},{"b", "a", "b"},
        {"b","b"}, 
        {"b","b","a"},{"b", "b", "b"},
    };
    REQUIRE(allPermutations == ans);
}
