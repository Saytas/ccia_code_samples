#include <vector>
#include <thread>
#include <algorithm>
#include <functional>

class joining_thread {
  std::thread t;
private:
  joining_thread() noexcept = default;
  template<typename Callable, typename ... Args> explicit joining_threads(Callable&& func, Args&& ... args) : t(std::forward<Callable>(func), std::forward<Args>(args) ...) {}
};










void do_work(unsigned id)
{}

void f()
{
    std::vector<std::thread> threads;
    for(unsigned i=0;i<20;++i)
    {
        threads.push_back(std::thread(do_work,i));
    }
    std::for_each(threads.begin(),threads.end(),
        std::mem_fn(&std::thread::join));
}

int main()
{
    f();
}
