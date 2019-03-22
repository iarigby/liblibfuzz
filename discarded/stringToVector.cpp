#include <sstream>
#include <vector>
#include <string>
#include <iostream>

std::vector<int> stringToVector(std::string str) {
    std::stringstream iss( str );
    int number;
    std::vector<int> myNumbers;
    while ( iss >> number ) 
        myNumbers.push_back( number );
    return myNumbers;
}

void test() {
    std::vector<int> vec = stringToVector("10 20");
    for(auto const& value: vec) {
        std::cout << value;
    }
    std::cout << std::endl;
}