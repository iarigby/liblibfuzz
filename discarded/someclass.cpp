class someclass {
public:
  void fun1(void);
  int fun2();
  int fun3(int a);
  std::vector<int> fun4();
};

void someclass::fun1(void) { std::cout << "inside fun1\n"; }

int someclass::fun2() {
  std::cout << "inside fun2\n";
  return 2;
}

int someclass::fun3(int a) {
  std::cout << "inside fun3\n";
  return a;
}

std::vector<int> someclass::fun4() {
  std::cout << "inside fun4\n";
  std::vector<int> v(4, 100);
  return v;
}