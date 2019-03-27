#ifndef FUNCTIONPOINTERMAP_H
#define FUNCTIONPOINTERMAP_H

#include <cassert>
#include <map>
#include <string>
#include <typeindex>
#include <typeinfo>
#include <vector>
#include <iostream>

template <typename A> using voidFunctionType = void (A::*)(void);
template <typename A> using voidFunction = void (*)(A&);

template <typename A> class FunctionPointerMap {
public:
  template <typename T> void insert(std::string s1, T f1);
  void insertNonVoid(std::string s1, voidFunction<A> f1);
  template <typename T, typename... Args>
  T searchAndCall(A &a, std::string s1, Args &&... args);

private:
  std::map<std::string, std::pair<voidFunctionType<A>, std::type_index>> m1;
  std::map<std::string, voidFunction<A>> m2;
  bool outputMessages = false;
};

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

#endif // FUNCTIONPOINTERMAP_H
