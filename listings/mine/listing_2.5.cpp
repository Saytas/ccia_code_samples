#include <iostream>
#include <string>
#include <thread>

void some_function() {
  std::cout << "some_function start and end" << std::endl;
  return;
}

void some_other_function(int) {
  std::cout << "some_other_function start and end" << std::endl;
  return;
}

std::thread f() {
  std::cout << "f start" << std::endl;
  void some_function();
  std::cout << "f end" << std::endl;
  return std::thread(some_function);
}
std::thread g() {
  std::cout << "g start" << std::endl;
  void some_other_function(int);
  std::thread t(some_other_function, 42);
  std::cout << "g end" << std::endl;
  return t;
}

int main() {
  std::cout << "main start" << std::endl;
  std::thread t1 = f();
  t1.join();
  std::thread t2 = g();
  t2.join();
  std::cout << "main end" << std::endl;
}
