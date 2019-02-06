#include "stack.cpp"

extern "C" {
  int __llvm_profile_runtime;  
  void __llvm_profile_initialize_file(void);
  int __llvm_profile_write_file(void);
  void __llvm_profile_set_filename(char *);
  void __llvm_profile_register_write_file_atexit(void);
	// __llvm_profile_set_filename("cov-test2.profraw");
	// __llvm_profile_initialize_file();
	// __llvm_profile_write_file();
} 

namespace {

class RegisterRuntime {
public:
  RegisterRuntime() {
  	__llvm_profile_set_filename("cov-test2.profraw");
    std::cout << "yay?\n" ;
    __llvm_profile_register_write_file_atexit();
    __llvm_profile_initialize_file();
    // __llvm_profile_write_file();
  }
};

	RegisterRuntime Registration;

}

void test1() {
	stack<int> pt(3);

    pt.push(1);
    pt.push(2);

    pt.pop();
    pt.pop();

    pt.push(3);

    std::cout << "Top element is: " << pt.peek() << std::endl;

    std::cout << "Stack size is " << pt.size() << std::endl;

    pt.pop();

    if (pt.isEmpty())
        std::cout << "Stack Is Empty\n";
    else
        std::cout << "Stack Is Not Empty\n";
}

void test2() {
	stack<int> pt(3);
	pt.pop();
}

// Stack implementation in C++
int main(int argc, const char **argv) {	
    test1();
    // return 0;
}
