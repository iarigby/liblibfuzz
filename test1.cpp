#include <iostream>
#include <unordered_map>


class TestInterface {
    public:
        int function1() {
            return 1;
        }
        int function2() {
            return 2;
        }
};

typedef int (TestInterface::*FunctionPointer) (void);
typedef std::unordered_map<int, FunctionPointer> Function_map;

int main() {
    Function_map m;
    TestInterface ts = TestInterface();
    m.emplace(0, (&TestInterface::function1));
    m.emplace(1, (&TestInterface::function2));
    for (int i = 0; i < 2; i++) {
        auto iter = m.find(i);
        if (iter != m.end()) {
            std::cout << (ts.*iter->second)() << std::endl;
        }
    }
    return 0;
}