#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>
#include <atomic>
#include <iostream>

class ThreadPool {
private:
    std::condition_variable_any condition;
    std::mutex queue_mutex;

    // Synchronization
    std::queue<std::function<void()>> tasks;
    std::vector<std::thread> workers;
    std::atomic<bool> stop;

    ThreadPool(const ThreadPool &) = delete;

    ThreadPool &operator=(const ThreadPool &) = delete;

public:
    ThreadPool(int workers_num) {
        for (size_t i = 0; i < workers_num; ++i) {
            workers.emplace_back(
                    [this]() {
                        while (!stop) {
                            std::function<void()> task;
                            {
                                std::unique_lock lock(queue_mutex);
                                condition.wait(lock, [this]() { return stop || !tasks.empty(); });
                                if (stop || tasks.empty()) {
                                    return;
                                }
                                task = std::move(tasks.front());
                                tasks.pop();
                            }
                            task();
                        }
                    }
            );
        }
    }

    ~ThreadPool() {
        stop.store(true);
        condition.notify_all();
        for (auto &worker : workers) {
            worker.join();
        }
    }

    template<typename F, typename... Args>
    auto enqueue(F &&f, Args &&...args) {
        using return_type = typename std::result_of<F(Args...)>::type;

        auto task = std::make_shared<std::packaged_task<return_type()>>
                (std::forward<F>(f), std::forward<Args>(args)...);

        std::future<return_type> res = task->get_future();
        {
            std::unique_lock lock(queue_mutex);
            if (stop) {
                throw std::runtime_error("Add Task Error!");
            }
            tasks.emplace([task]() {
                (*task)();
            });
        }
        condition.notify_one();
        return res;
    }

};

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