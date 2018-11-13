#include <iostream>

class TestInterface {
    public:
        int function1() {
            return 1;
        }
};

int main() {
    TestInterface ts = TestInterface();
    std::cout << ts.function1() << std::endl;
    return 0;
}