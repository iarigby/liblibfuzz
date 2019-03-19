#include "functionPointerMap.h"
#include <iostream>

template <typename A> using voidFunctionType = void (A::*)(void);
template <typename A> using voidFunction = void (*)(A&);

template <typename A>
template <typename T>
void FunctionPointerMap<A>::insert(std::string s1, T f1) {
  auto tt = std::type_index(typeid(f1));
  m1.insert(std::make_pair(s1, std::make_pair((voidFunctionType<A>)f1, tt)));
}

template <typename A>
void FunctionPointerMap<A>::insertNonVoid(std::string s1, voidFunction<A> f2) {
  m2.insert(std::make_pair(s1, f2));
}

template <typename A>
template <typename T, typename... Args>
T FunctionPointerMap<A>::searchAndCall(A &a, std::string s1, Args &&... args) {
  if (this->outputMessages) {
    std::cout << "calling " << s1 << "\n";
  }
  auto mapIter = m1.find(s1);
  if (mapIter != m1.end()) {
    auto mapVal = mapIter->second;
    auto typeCastedFun = (T(A::*)(Args...))(mapVal.first);
    // removed because right now it is cast back to void
    // maybe mapVal.second can be used somewhere
    // TODO research type_index usage
    // assert(mapVal.second == std::type_index(typeid(typeCastedFun)));
    return (a.*typeCastedFun)(std::forward<Args>(args)...);
  } else {
    return (m2.find(s1)->second)(a);
  }
  
}
