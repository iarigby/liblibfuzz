#include <iostream>
#include <vector>
#include "functionPointerMap.cpp"
#include <string>
#include "stack.cpp"

std::map<std::vector<std::string>, std::vector<std::string>> pcCalls;
std::vector<std::string> currentPermutation;
// trace-pc-guard-example.cc
using permutations = std::vector<std::vector<std::string>>;
permutations getAllPossibleSequences(std::vector<std::string> v, int maxSize);
permutations getSubsets(std::vector<std::string> v);

int main(int argc, char **argv) {
	FunctionPointerMap<stack<int>> a1;
	// a1.insert("push", &stack<int>::push);
	a1.insert("pop", &stack<int>::pop);
	a1.insert("peek", &stack<int>::peek);
	a1.insert("size", &stack<int>::size);
	a1.insert("isEmpty", &stack<int>::isEmpty);
	a1.insert("isFull", &stack<int>::isFull);
	std::vector<std::string> v = {"pop", "peek", "size", "isEmpty", "isFull"};
	permutations p = getAllPossibleSequences(v, 4);
	std::cout << "here" << std::endl;
	for (auto const perm : p) {
		currentPermutation = perm;
		stack<int> s(5);
		// s.push(1);
		// s.push(2);
		// s.push(3);
		std::cout << "***** perm";
		for (auto const elem : perm) 
			std::cout << " " << elem;
		std::cout << "\n";
		for (auto const elem : perm) {
			// a1.searchAndCall<void>(s, elem);	
		}
		std::cout << std::endl;
	}
}

// ATTRIBUTE_NO_SANITIZE_ADDRESS
permutations getSubsets(std::vector<std::string> v) {
	permutations allSubsets;
	for (auto const iter : v) {
		std::vector<std::string> oneElemSet;
		oneElemSet.push_back(iter);
		allSubsets.push_back(oneElemSet);
		for (auto const setsIter : allSubsets) {
			if (!(setsIter.size() == 1 && setsIter[0] == iter)) {
				std::vector<std::string> set;
				//TODO maybe not necessary to copy one by one
				for (auto const setElem : setsIter) {
					set.push_back(setElem);
				}
				set.push_back(iter);
				allSubsets.push_back(set);
			}			
		}
	}
	return allSubsets;
}

// ATTRIBUTE_NO_SANITIZE_ADDRESS
permutations getAllPossibleSequences(std::vector<std::string> v, int maxSize) {
	permutations p; 
	// get all subsets
	permutations allSubsets = getSubsets(v);
	// include all duplicate elements
	// permute all subsets
	return allSubsets;
}