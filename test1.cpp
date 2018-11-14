#include "stringToVector.cpp"
#include <iostream>
#include <string>
#include <unordered_map>

const int numFunctions = 5;
class TestInterface {
public:
  int function1() { return 1; }
  int function2() { return 2; }
  int function3() { return 15; }
  int function4() { return function3() * function2(); }
  int function5() { return function1(); }
};

using FunctionPointer = int (TestInterface::*)();
using Function_map = std::unordered_map<int, FunctionPointer> ;

int test(TestInterface ts, Function_map m) {
  for (int i = 0; i < 2; i++) {
    auto iter = m.find(i);
    if (iter != m.end()) {
      std::cout << (ts.*iter->second)() << std::endl;
    }
  }
  return 0;
}

bool isValidCallSequence(std::vector<int> vec) {
  for (auto i : vec) {
    if (i < 0 || (i > numFunctions))
      return false;
  }
  return true;
}

void callFunctions(std::vector<int> vec, TestInterface ts, Function_map m) {
  std::cout << "got it: ";
  for (auto i : vec) {
    auto iter = m.find(i);
    if (iter != m.end()) {
      std::cout << (ts.*iter->second)() << " > ";
      (ts.*iter->second)();
    }
  }
  std::cout << std::endl;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  Function_map m;
  TestInterface ts = TestInterface();
  m.emplace(0, (&TestInterface::function1));
  m.emplace(1, (&TestInterface::function2));
  m.emplace(2, (&TestInterface::function3));
  m.emplace(3, (&TestInterface::function4));
  m.emplace(4, (&TestInterface::function5));
  std::string str;
  str.reserve(Size);
  for (std::size_t i = 0; i < Size; i++) {
    str += std::to_string(Data[i]) + ' ';
  }
  std::vector<int> vec = stringToVector(str);
  std::cout << str << std::endl;
  if (isValidCallSequence(vec)) {
    // std::cout << str << std::endl;
    callFunctions(vec, ts, m);
  }
  return 0;
}