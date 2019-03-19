#include "stack.cpp"

void test1() {
	stack<int> pt(3);

    pt.push(1);
    pt.push(2);

    pt.pop();
    pt.pop();

    pt.push(3);

    std::cout << "Top element is: " << pt.peek() << std::endl;

    std::cout << "Stack size is " << pt.size() << std::endl;

    pt.pop();

    if (pt.isEmpty())
        std::cout << "Stack Is Empty\n";
    else
        std::cout << "Stack Is Not Empty\n";
}

void test2() {
	stack<int> pt(3);
	pt.pop();
}

// Stack implementation in C++
int main(int argc, const char **argv) {	
    test1();
    // return 0;
}
