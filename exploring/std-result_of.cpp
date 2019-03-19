#include <type_traits>
#include "functionPointerMap.cpp"

class myclass {
    void f1() {

    }
    int f2(bool) {
        return 3;
    }
};


int main() {
    FunctionPointerMap<myClass> a1;
    a1.insert()

}