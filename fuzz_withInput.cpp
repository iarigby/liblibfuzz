#include "INTERFACEWITHINPUT.h"
#include "stringToVector.cpp"
#include <iostream>
#include <string>
#include <unordered_map>

const int numFunctions = 4;

using FunctionPointer = int (InterfaceWithInput::*)(int);
using Function_map = std::unordered_map<int, FunctionPointer> ;

bool isValidCallSequence(std::vector<int> vec);
void callFunctions(std::vector<int> vec, InterfaceWithInput ts, Function_map m);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  Function_map m;
  InterfaceWithInput ts = InterfaceWithInput();
  m.emplace(0, (&InterfaceWithInput::function1));
//   m.emplace(1, (&InterfaceWithInput::function2));
//   m.emplace(2, (&InterfaceWithInput::function3));
//   m.emplace(3, (&InterfaceWithInput::function5));
  std::string str;
  str.reserve(Size);
  for (std::size_t i = 0; i < Size; i += 2) {
    str += std::to_string(Data[i]) + ' ';
  }
  std::vector<int> vec = stringToVector(str);
//   std::cout << str << std::endl;
  if (isValidCallSequence(vec)) {
    // std::cout << str << std::endl;
    callFunctions(vec, ts, m);
  }
  return 0;
}

bool isValidCallSequence(std::vector<int> vec) {
  if (vec.size() % 2 != 0) {
      return false;
  }
  for (auto i : vec) {
    if (i < 0 || (i > numFunctions))
      return false;
  }
  return true;
}

void callFunctions(std::vector<int> vec, InterfaceWithInput ts, Function_map m) {
//   std::cout << "got it: ";
  for (std::size_t i = 0; i < vec.size(); i += 2) {
    auto iter = m.find(vec[i]);
    if (iter != m.end()) {
    //   std::cout << (ts.*iter->second)(vec[i+1]) << " > ";
      (ts.*iter->second)(vec[i+1]);
    }
  }
//   std::cout << std::endl;
}