#include <iostream>
#include <string>
#include <vector>
#include <variant>
#include <iomanip>

using var_t = std::variant<int, long, double, std::string>;

template<class... Ts> struct overloaded : Ts... { using Ts ::operator()...;};
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

int main() {
    std::vector<var_t> vec = {10, 15L, 1.5, "hello"};

    for (auto& v : vec) {
        std::visit(overloaded {
            [](auto arg) { std::cout << arg << "<< ";},
            [](int arg) { std::cout << arg << "** "; },
            [](double arg) { std::cout << std::fixed << arg << ' ';},
            [](const std::string& arg) {std::cout << std::quoted(arg) << ' ';},
        }, v);
    }
}

// could store all possible combinations of inputs 

// store return types 