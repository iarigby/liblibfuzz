#include "functionPointerMap.cpp"
#include "discarded/someclass.cpp"
#include "stack.cpp"

/*
void testSomeClass() {
	FunctionPointerMap<someclass> a1;
	a1.insert("fun3", &someclass::fun3);
	someclass s;
	int retVal = a1.searchAndCall<int>(s, "fun3", 3);
	std::cout << retVal << std::endl;
}

void testStack() {
	FunctionPointerMap<stack<int>> a1;
	a1.insert("push", &stack<int>::push);
	a1.insert("pop", &stack<int>::pop);
	stack<int> s(10);
	// TODO does not work
	// in push, top, arr[top] are 0, 3
	// when entering pop, it's -1 and 0 
	a1.searchAndCall<void>(s, "push", 3);
	// s.push(3); searchAndCall pop works with this
	int retVal = a1.searchAndCall<int>(s, "pop");
	std::cout << retVal << "\n";
	s.push(5);
	retVal = a1.searchAndCall<int>(s, "pop");
	std::cout << retVal << "\n";
}
*/
int main() {
  // testStack();
  std::cout << "end\n";
  return 0;
}

