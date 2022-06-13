#include <iostream>
#include <thread>

void do_something(int& i) {
  ++i;
}

struct func {
  int& i;
  func(int& i_) : i(i_){}
  void operator()() {
    std::cout << "operator start" << std::endl;
    for(unsigned j = 0; j < 1000000; ++j) {
      do_something(i);
    }
    std::cout << "i = " << i << std::endl;
    std::cout << "operator end" << std::endl;
  }
};

void do_something_in_current_thread() {
  std::cout << "do_something_in_current_thread start and end" << std::endl;
}

void f() {
  std::cout << "f start" << std::endl;
  int some_local_state = 0;
  func my_func(some_local_state);
  std::thread t(my_func);
  try {
    std::cout << "try block start" << std::endl;
    do_something_in_current_thread();
    std::cout << "try block end" << std::endl;
  } catch(...) {
    std::cout << "catch block start" << std::endl;
    t.join();
    throw;
    std::cout << "catch block end" << std::endl;
  }
  t.join();
  std::cout << "f end" << std::endl;
}

int main() {
  std::cout << "main start" << std::endl;
  f();
  std::cout << "main end" << std::endl;
}
