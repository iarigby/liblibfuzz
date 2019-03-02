#ifndef FUNCTIONPOINTERMAP_H
#define FUNCTIONPOINTERMAP_H

#include <string>
#include <map>
#include <typeinfo>
#include <typeindex>
#include <cassert>
#include <vector>
#include <tuple>

template <typename A>
using voidFunctionType = void (A::*)(void);

template <typename A, typename R>
class FunctionPointerMap {
public:
    template <typename T>
    void insert(std::string s1, T f1, std::tuple<R> args);
    template <typename T>
    void insert(std::string s1, T f1);
    template<typename T>
    T searchAndCall(A &a, std::string s1);
private:
    std::map<std::string,std::tuple<voidFunctionType<A>,std::type_index, std::tuple<R>>> m1;
    bool outputMessages = false;
};


#endif // FUNCTIONPOINTERMAP_H
