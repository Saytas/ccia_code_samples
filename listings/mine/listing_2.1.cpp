#include <iostream>
#include <thread>

// Displays an undefined behaviour

void do_something(int& i) {
  ++i;
  return;
}

struct func {
  //std::cerr << "func start" << std::endl;
  int& i;
  func(int& i_) : i(i_){}
  void operator()() {
    std::cout << "operator start" << std::endl;
    for(unsigned j = 0; j < 1000000; ++j) {
      do_something(i);
    }
    std::cout << "operator end" << std::endl;
  }
  //std::cerr << "func end" << std::endl;
};


void oops() {
  std::cout << "oops start" << std::endl;
  int some_local_state = 0;
  func my_func(some_local_state);
  std::thread my_thread(my_func);
  // If you need to wait for a thread to complete,
  // you can do this by calling join() on the
  // associated std::thread instance. join() is a
  // simple and brute-force technique either you
  // wait for a thread to fin- ish or you don’t
  // The act of calling join() also cleans up any
  // storage associ- ated with the thread, so the
  // std::thread object is no longer associated with
  // the now- finished thread; it isn’t associated
  // with any thread. This means that you can call
  // join() only once for a given thread; once you’ve
  // called join(), the std::thread object is no longer
  // joinable, and joinable() will return false
  my_thread.join();
  // In this case, the new thread associated with
  // my_thread will probably still be running when
  // oops exits, because you’ve explicitly decided
  // not to wait for it by calling detach()
  //my_thread.detach();
  std::cout << "oops end" << std::endl;
  return;
}

int main() {
  std::cout << "main start" << std::endl;
  oops();
  std::cout << "main end" << std::endl;
}
