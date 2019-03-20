#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "combinationGenerator.cpp"
#include <vector>
#include <string>

TEST_CASE("combination generation test", "[combinationgenerator]") {
    std::vector<std::string> vec = {"a", "b"};
    CombinationGenerator<std::string> cb(vec, 3);
    std::vector<std::vector<std::string>> allCombinations;
    int i = 0;
    while (!cb.isDone() && i<100) {
        i++;
        allCombinations.push_back(cb.nextCombination());
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
    REQUIRE(allCombinations == ans);
}
