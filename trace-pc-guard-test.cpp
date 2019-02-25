#include <iostream>
#include <vector>
#include "functionPointerMap.cpp"
#include <string>
#include "stack.cpp"
#include "combinationGenerator.cpp"

std::map<std::vector<std::string>, std::vector<std::string>> pcCalls;
std::vector<std::string> currentPermutation;
// trace-pc-guard-example.cc

int main(int argc, char **argv) {
	FunctionPointerMap<stack<int>> a1;
	// a1.insert("push", &stack<int>::push);
	a1.insert("pop", &stack<int>::pop);
	a1.insert("peek", &stack<int>::peek);
	a1.insert("size", &stack<int>::size);
	a1.insert("isEmpty", &stack<int>::isEmpty);
	a1.insert("isFull", &stack<int>::isFull);
	std::vector<std::string> v = {"pop", "peek", "size", "isEmpty", "isFull"};
	CombinationGenerator<std::string> cb(v, 3);
	while (!cb.isDone()) {
		auto perm = cb.nextCombination();
		currentPermutation = perm;
		stack<int> s(5);
		s.push(1);
		s.push(2);
		s.push(3);
		std::cout << "***** perm";
		for (auto const elem : perm) 
			std::cout << " " << elem;
		std::cout << "\n";
		for (auto const elem : perm) {
			a1.searchAndCall<void>(s, elem, 3);	
		}
		std::cout << std::endl;
	}
}