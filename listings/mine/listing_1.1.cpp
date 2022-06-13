#include <iostream>
#include <thread>

void hello() {
  std::cout << "Hello Concurrent World" << std::endl;
  return;
}

int main() {
  std::thread t(hello);
  t.join();
}
