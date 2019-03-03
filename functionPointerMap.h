#ifndef FUNCTIONPOINTERMAP_H
#define FUNCTIONPOINTERMAP_H

#include <string>
#include <map>
#include <typeinfo>
#include <typeindex>
#include <cassert>
#include <vector>
#include <tuple>

#include <any>

template <typename A>
using voidFunctionType = void (A::*)(void);

template <typename A>
class FunctionPointerMap {
public:
    template <typename T>
    void insert(std::string s1, T f1, std::tuple<std::any> args);
    template <typename T>
    void insert(std::string s1, T f1);
    template<typename T>
    T searchAndCall(A &a, std::string s1);
private:
    std::map<std::string,std::tuple<voidFunctionType<A>,std::type_index, std::tuple<std::any>>> m1;
    bool outputMessages = false;
};


#endif // FUNCTIONPOINTERMAP_H
