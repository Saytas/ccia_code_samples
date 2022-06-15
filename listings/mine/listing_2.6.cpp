#include <iostream>
#include <string>
#include <thread>
#include <utility>

class scoped_thread {
  std::thread t;
public:
  explicit scoped_thread(std::thread t_) : t(std::move(t_)) { // constructor with initializer list
    if(!t.joinable()) {
      throw std::logic_error("No thread");
    }
  }
  ~scoped_thread() { // destructor
    t.join();
  }
  scoped_thread(scoped_thread const&) = delete; // copy constructor
  scoped_thread& operator=(scoped_thread const&) = delete; // copy-assignment operator
};

void do_something(int& i) {
  ++i;
  return;
}

struct func {
  int& i;
  func(int& i_) : i(i_) {}
  void operator()() {
    std::cout << "operator start" << std::endl;
    for (unsigned j = 0; j < 1000000; ++j) {
      do_something(i);
    }
    std::cout << "operator end" << std::endl;
  }
};

void do_something_in_current_thread() {
  std::cout << "do_something_in_current_thread start and end" << std::endl;
  return;
}

void f() {
  std::cout << "f start" << std::endl;
  int some_local_state;
  scoped_thread t{std::thread(func(some_local_state))};
  //scoped_thread t(std::thread(func(some_local_state)));
  do_something_in_current_thread();
  std::cout << "f end" << std::endl;
}

int main() {
  std::cout << "main start" << std::endl;
  f();
  std::cout << "main end" << std::endl;
}
