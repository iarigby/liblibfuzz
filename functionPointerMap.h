#ifndef FUNCTIONPOINTERMAP_H
#define FUNCTIONPOINTERMAP_H

#include <cassert>
#include <map>
#include <string>
#include <typeindex>
#include <typeinfo>
#include <vector>

template <typename A> using voidFunctionType = void (A::*)(void);

template <typename A> class FunctionPointerMap {
public:
  template <typename T> void insert(std::string s1, T f1);
  template <typename T, typename... Args>
  T searchAndCall(A &a, std::string s1, Args &&... args);

private:
  std::map<std::string, std::pair<voidFunctionType<A>, std::type_index>> m1;
  bool outputMessages = false;
};

#endif // FUNCTIONPOINTERMAP_H
