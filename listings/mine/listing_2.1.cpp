#include <iostream>
#include <thread>

// Displays an undefined behaviour

void do_something(int& i) {
  ++i;
  return;
}

struct func {
  //std::cout << "func start" << std::endl;
  int& i;
  func(int& i_) : i(i_){}
  void operator()() {
    std::cout << "operator start" << std::endl;
    for(unsigned j = 0; j < 1000000; ++j) {
      do_something(i);
    }
    std::cout << "operator end" << std::endl;
  }
  //std::cout << "func end" << std::endl;
};


void oops() {
  std::cout << "oops start" << std::endl;
  int some_local_state = 0;
  func my_func(some_local_state);
  std::thread my_thread(my_func);
  // In this case, the new thread associated with
  // my_thread will probably still be running when
  // oops exits, because you’ve explicitly decided
  // not to wait for it by calling detach()
  my_thread.detach();
  std::cout << "oops end" << std::endl;
  return;
}

int main() {
  std::cout << "main start" << std::endl;
  oops();
  std::cout << "main end" << std::endl;
}
