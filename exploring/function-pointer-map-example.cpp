#include <cassert>
#include <iostream>
#include <map>
#include <string>
#include <typeindex>
#include <typeinfo>
#include <vector>

// every function pointer will be stored as this type
// typedef void (*voidFunctionType)(void);

template <typename A> using voidFunctionType = void (A::*)(void);

template <typename A> struct Interface {

  // we store pointers as voids
  std::map<std::string, std::pair<voidFunctionType<A>, std::type_index>> m1;

  template <typename T> void insert(std::string s1, T f1) {
    auto tt = std::type_index(typeid(f1));
    m1.insert(std::make_pair(s1, std::make_pair((voidFunctionType<A>)f1, tt)));
  }

  template <typename T, typename... Args>
  // && is a universal reference
  T searchAndCall(A a, std::string s1, Args &&... args) {
    auto mapIter = m1.find(s1);
    /*chk if not end*/
    auto mapVal = mapIter->second;

    // converted to actual signature here
    // reinterpret cast
    // auto typeCastedFun = reinterpret_cast<T(*)(Args ...)>(mapVal.first);
    auto typeCastedFun = (T(A::*)(Args...))(mapVal.first);

    // compare the types is equal or not
    assert(mapVal.second == std::type_index(typeid(typeCastedFun)));
    return (a.*typeCastedFun)(std::forward<Args>(args)...);
  }
};

class someclass {
public:
  void fun1(void);
  int fun2();
  int fun3(int a);
  std::vector<int> fun4();
};

void someclass::fun1(void) { std::cout << "inside fun1\n"; }

int someclass::fun2() {
  std::cout << "inside fun2\n";
  return 2;
}

int someclass::fun3(int a) {
  std::cout << "inside fun3\n";
  return a;
}

std::vector<int> someclass::fun4() {
  std::cout << "inside fun4\n";
  std::vector<int> v(4, 100);
  return v;
}

int main() {
  Interface<someclass> a1;
  a1.insert("fun3", &someclass::fun3);
  someclass s;
  int retVal = a1.searchAndCall<int>(s, "fun3", 3);
  std::cout << retVal;
  return 0;
}
