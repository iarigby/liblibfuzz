#include "functionPointerMap.h"
#include <iostream>
#include <vector>

template <typename A> 
using voidFunctionType = void (A::*)(void);

template <typename A>
template <typename T> 
void FunctionPointerMap<A>::insert(std::string s1, T f1) {
  auto tt = std::type_index(typeid(f1));
  m1.insert(std::make_pair(s1, std::make_pair((voidFunctionType<A>)f1, tt)));
}

template <typename A>
template <typename T, typename... Args>
T FunctionPointerMap<A>::searchAndCall(A a, std::string s1, Args &&... args) {
  std::cout << "calling " << s1 << "\n";
  auto mapIter = m1.find(s1);
  auto mapVal = mapIter->second;
  auto typeCastedFun = (T(A::*)(Args...))(mapVal.first);
  assert(mapVal.second == std::type_index(typeid(typeCastedFun)));
  return (a.*typeCastedFun)(std::forward<Args>(args)...);
}

