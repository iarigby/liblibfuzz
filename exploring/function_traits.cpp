// source https://stackoverflow.com/a/9065203
#include <functional>
#include <type_traits>
#include <typeinfo>
#include <iostream>
template<typename T> 
struct function_traits;  


//I think this can be simplified with using
template<typename R, typename ...Args> 
struct function_traits<std::function<R(Args...)>>
{
    static const size_t nargs = sizeof...(Args);

    typedef R result_type;

    template <size_t i>
    struct arg
    {
        typedef typename std::tuple_element<i, std::tuple<Args...>>::type type;
    };
};


struct R{};
struct A{};
struct B{};

R something(A a, B b) {
    R r;
    return r;
}

int main()
{
//    typedef std::function<R(A,B)> fun;

   std::cout << std::is_same<R, function_traits<std::function<decltype(something)>>::result_type>::value << std::endl;
   std::cout << std::is_same<A, function_traits<std::function<decltype(something)>>::arg<0>::type>::value << std::endl;
   std::cout << std::is_same<B, function_traits<std::function<decltype(something)>>::arg<1>::type>::value << std::endl;
} 

