#include "functionPointerMap.h"
#include <iostream>
#include <vector>
#include <utility>

template <typename A> 
using voidFunctionType = void (A::*)(void);

template <typename A, typename R>
template <typename T> 
void FunctionPointerMap<A, R>::insert(std::string s1, T f1, std::tuple<R> args) {
  auto tt = std::type_index(typeid(f1));
  m1.insert(std::make_pair(s1, std::make_tuple((voidFunctionType<A>)f1, tt, args)));
}

template <typename A, typename R>
template <typename T> 
void FunctionPointerMap<A, R>::insert(std::string s1, T f1) {
  auto tt = std::type_index(typeid(f1));
  m1.insert(std::make_pair(s1, std::make_tuple((voidFunctionType<A>)f1, tt, 0)));
}


template <typename A, typename R>
template <typename T>
T FunctionPointerMap<A, R>::searchAndCall(A &a, std::string s1) {
  if (this->outputMessages) {
    std::cout << "calling " << s1 << "\n";
  }
  auto mapIter = m1.find(s1);
  auto mapVal = mapIter->second;
  // auto typeCastedFun = (T(A::*)(Args...))(std::get<0>(mapVal));
  // removed because right now it is cast back to void
  // maybe mapVal.second can be used somewhere
  // TODO research type_index usage
  // assert(mapVal.second == std::type_index(typeid(typeCastedFun)));
  // https://stackoverflow.com/a/36612797
  // https://stackoverflow.com/questions/7858817/unpacking-a-tuple-to-call-a-matching-function-pointer/9288547#9288547
  // return (a.*typeCastedFun)(std::forward<Args>(std::get<2>(mapVal)));
  return std::apply(((T(A::*)(R...))(std::get<0>(mapVal))),std::get<2>(mapVal));
}

