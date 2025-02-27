#include <iostream>
#include <thread>

class thread_guard {
  std::thread& t;
public:
  explicit thread_guard(std::thread& t_) : t(t_) {}
  ~thread_guard() {
    std::cout << "~thread_guard start" << std::endl;
    if(t.joinable()) {
      std::cout << "t.joinable() start" << std::endl;
      t.join();
      std::cout << "t.joinable() end" << std::endl;
    }
    std::cout << "~thread_guard end" << std::endl;
  }
  // The copy constructor and copy-assignment operators
  // are marked =delete to ensure that they’re not
  // automatically provided by the compiler. Copying or
  // assigning such an object would be dangerous, because
  // it might then outlive the scope of the thread it was
  // joining. By declaring them as deleted, any attempt to
  // copy a thread_guard object will generate a compilation error
  thread_guard(thread_guard const&) = delete; // copy constructor
  thread_guard& operator=(thread_guard const&) = delete; // copy-assignment operator
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
    for(unsigned j = 0; j < 1000000; ++j) {
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
  func my_func(some_local_state);
  std::thread t(my_func);
  thread_guard g(t);
  do_something_in_current_thread();
  std::cout << "f end" << std::endl;
}

int main() {
  std::cout << "main start" << std::endl;
  f();
  std::cout << "main end" << std::endl;
}

