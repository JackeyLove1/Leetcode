#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>


#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>

class ThreadPool {
public:
    // 构造函数， 初始化大小
    ThreadPool(size_t);

    // typename std::result<F(Args...)> -> 编译期推断返回类型
    // 可以使用auto代替，自动推断返回类型
    template<class F, class... Args>
    auto enqueue(F &&f, Args &&... args)
    -> std::future<typename std::result_of<F(Args...)>::type>;

    // 析构函数
    ~ThreadPool();

private:
    // need to keep track of threads so we can join them
    // 线程池的工作线程数
    std::vector<std::thread> workers;

    // the task queue
    // 任务队列 函数应该被包装为void(void) 的task
    std::queue<std::function<void()> > tasks;

    // synchronization
    // 同步工具
    // 互斥锁和条件变量
    // stop变量检测是否关闭线程池，可以使用atomic<bool>代替
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;
};

// the constructor just launches some amount of workers
inline ThreadPool::ThreadPool(size_t threads)
        : stop(false) {
    // 创建threads个新线程塞进线程池
    // 使用std::move 右值传递
    for (size_t i = 0; i < threads; ++i)
        workers.emplace_back( // 相当于 push_back(std::move(...))
                [this] { // lambda函数，将class的成员变量以指针（引用）形式传递进去，*this则是以拷贝形式传递
                    for (;;) {
                        // worker函数不断轮询，竞争任务
                        // 创建一个任务包装，以存放将要完成的task
                        std::function<void()> task;
                        {
                            // 访问临界区需要上锁
                            std::unique_lock<std::mutex> lock(this->queue_mutex);
                            // 若队列不为空或者需要stop，则唤醒worker
                            this->condition.wait(lock,
                                                 [this] { return this->stop || !this->tasks.empty(); });
                            // 若有停止信号或者队列为空，则直接返回
                            if (this->stop && this->tasks.empty())
                                return;
                            // 获取任务，使用右值
                            task = std::move(this->tasks.front());
                            // 弹出在工作的任务
                            this->tasks.pop();
                        }
                        // 执行任务
                        task();
                        // 完成后继续从task队列中提取任务
                    }
                }
        );
}

// add new work item to the pool
template<class F, class... Args>
auto ThreadPool::enqueue(F &&f, Args &&... args)
// 下面的推断可以使用auto
-> std::future<typename std::result_of<F(Args...)>::type> {
    // 使用萃取的方法获取返回值类型
    using return_type = typename std::result_of<F(Args...)>::type;
    // 等价于
    // using RetType = decltype(f(args...));
    // 将任务包装成异步函数指针，封装为shared_ptr 完后后自动回收，不造成内存泄漏
    // 而且在后续的lambda函数中可以直接传递函数指针然后执行
    // 使用packaged_task<>，函数绑定std::bind，和完美转发std::forward
    // 包装需要执行的函数，然后在后台进行异步执行
    auto task = std::make_shared<std::packaged_task<return_type()> >(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...));

    // 绑定异步函数task的返回值到future res中
    std::future<return_type> res = task->get_future();

    {
        // 在匿名作用域中使用unique_lock
        // 减小锁的粒度，出了匿名作用区锁就被释放
        std::unique_lock<std::mutex> lock(queue_mutex);

        // don't allow enqueueing after stopping the pool
        // 防止在停止后放入任务
        if (stop)
            throw std::runtime_error("enqueue on stopped ThreadPool");

        // 将匿名函数包装到lambda函数void()中
        // task是函数指针（即函数的地址），所以拷贝传递可以执行
        tasks.emplace([task]() { (*task)(); });
    }
    // 唤醒一个worker
    condition.notify_one();
    return res;
}

// the destructor joins all threads
inline ThreadPool::~ThreadPool() {
    {
        // 此处使用atomic<bool>显得更加方便
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop = true;
    }
    condition.notify_all();
    // join后自动销毁回收
    for (std::thread &worker: workers)
        worker.join();
}


#include <iostream>

int main() {

    ThreadPool pool(4);
    std::vector<std::future<int> > results;

    results.reserve(8);
    for (int i = 0; i < 8; ++i) {
        results.emplace_back(
                pool.enqueue([i] {
                    std::cout << "hello " << i << std::endl;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    std::cout << "world " << i << std::endl;
                    return i * i;
                })
        );
    }

    for (auto &&result: results)
        std::cout << result.get() << ' ';
    std::cout << std::endl;

    return 0;
}