#include <iostream>
#include <unordered_map>


class TestInterface {
    public:
        int function1() {
            return 1;
        }
};
    
int main() {
    TestInterface ts = TestInterface();
    int (TestInterface::*fptr) (void) = &TestInterface::function1;
    std::cout << (ts.*fptr)() << std::endl;
    return 0;
}