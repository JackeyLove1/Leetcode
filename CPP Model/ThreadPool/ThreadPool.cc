#include <memory>
#include <list>
#include <atomic>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>

class NoCopy {
protected:
    NoCopy() = default;

    ~NoCopy() = default;

    NoCopy(const NoCopy &) = delete;

    NoCopy &operator=(const NoCopy &) = delete;
};

constexpr int MaxTaskCount = 100;
constexpr int DEBUG = 1;

template<typename T>
class SyncQueue : public NoCopy {
public:
    SyncQueue(int maxSize) : m_maxSize(maxSize), m_needStop(false) {}

    void Put(const T &x) {
        Add(x);
    }

    void Put(T &&x) {
        Add(std::forward<T>(x));
    }

    void Take(T &t) {
        std::unique_lock locker(m_mutex);
        if (DEBUG) printf("I am waiting ... \n");
        m_notEmpty.wait(locker, [this]() { return m_needStop || NotEmpty(); });
        if (m_needStop) {
            return;
        }
        t = m_queue.front();
        m_queue.pop_front();
        m_notFull.notify_one();
    }

    void Take(std::list<T> &list) {
        std::unique_lock locker(m_mutex);
        m_notEmpty.wait(locker, [this]() { return m_needStop || NotEmpty(); });
        if (m_needStop) {
            return;
        }
        list = std::move(m_queue);
        m_notEmpty.notify_one();
    }

    void Stop() {
        {
            std::lock_guard locker(m_mutex);
            m_needStop = true;
        }
        m_notFull.notify_all();
        m_notEmpty.notify_all();
    }

    bool Full() {
        std::lock_guard locker(m_mutex);
        return m_queue.size() >= m_maxSize;
    }

    bool Empty() {
        std::lock_guard locker(m_mutex);
        return m_queue.empty();
    }

    size_t Size() {
        std::lock_guard locker(m_mutex);
        return m_queue.size();
    }

    int Count() {
        return m_queue.size();
    }

private:
    bool NotFull() const {
        bool full = m_queue.size() >= m_maxSize;
        if (full && DEBUG) {
            std::cout << "m_queue is full " << std::endl;
        }
        return !full;
    }

    bool NotEmpty() const {
        bool empty = m_queue.empty();
        if (empty && DEBUG) {
            std::cout << "m_queue is empty " << std::endl;
        }
        return !empty;
    }

    template<typename F>
    void Add(F &&x) {
        std::unique_lock locker(m_mutex);
        m_notFull.wait(locker, [this]() { return m_needStop || NotFull(); });
        if (m_needStop) {
            return;
        }
        m_queue.push_back(std::forward<F>(x));
        m_notEmpty.notify_one();
    }

private:
    std::list<T> m_queue;
    std::mutex m_mutex;
    std::condition_variable m_notEmpty;
    std::condition_variable m_notFull;
    int m_maxSize;
    bool m_needStop;
};

void TestSyncQueue() {
    SyncQueue<int> sq(5);
    std::thread t2([&]() {
        int n;
        for (int i = 1; i <= 10; ++i) {
            sq.Take(n);
            printf("c1 receive %d\n", n);
        }
    });
    std::thread t1([&]() {
        for (int i = 1; i <= 10; ++i) {
            sq.Put(i);
            printf("p1 send %d\n", i);
            // std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });
    std::thread t3([&]() {
        for (int i = 1; i <= 10; ++i) {
            sq.Put(i);
            printf("p3 send %d\n", i);
            // std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });
    std::thread t4([&]() {
        int n;
        for (int i = 1; i <= 10; ++i) {
            sq.Take(n);
            printf("c2 receive %d\n", n);
        }
    });
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    sq.Stop();
}


class ThreadPool : public NoCopy {
public:
    using Task = std::function<void()>;

    ThreadPool(int numThreads = std::thread::hardware_concurrency()) : m_queue(MaxTaskCount) {
        Start(numThreads);
    }

    ~ThreadPool() {
        Stop();
    }

public:
    void Stop() {
        std::call_once(m_flag, [this]() { StopThreadGroup(); });
    }

    void AddTask(Task &&task) {
        m_queue.Put(std::forward<Task>(task));
    }

    void AddTask(const Task &task) {
        m_queue.Put(task);
    }

    void Start(int numThreads) {
        m_running = true;
        for (int i = 0; i < numThreads; ++i) {
            m_threadgroup.push_back(std::make_shared<std::thread>(
                    &ThreadPool::RunInThread, this
            ));
        }
    }

private:
    void RunInThread() {
        while (m_running) {
            std::list<Task> list;
            m_queue.Take(list);
            for (auto &task : list) {
                if (!m_running) {
                    return;
                }
                task();
            }
        }
    }

    void StopThreadGroup() {
        m_queue.Stop();
        m_running = false;
        for (auto &&thread : m_threadgroup) {
            if (thread) {
                thread->join();
            }
        }
        m_threadgroup.clear();
    }

private:
    std::list<std::shared_ptr<std::thread>> m_threadgroup;
    SyncQueue<Task> m_queue;
    std::atomic<bool> m_running;
    std::once_flag m_flag;
};

// test
using namespace std;

void TestThreadPool() {
    ThreadPool pool;
    pool.Start(2);
    std::thread td1([&pool] {
        for (int i = 0; i < 10; ++i) {
            auto thdId = std::this_thread::get_id();
            pool.AddTask([thdId] {
                cout << "I am thread1 " << thdId << endl;
            });
        }
    });
    std::thread td2([&pool] {
        for (int i = 0; i < 10; ++i) {
            auto thdId = std::this_thread::get_id();
            pool.AddTask([thdId] {
                cout << "I am thread2 " << thdId << endl;
            });
        }
    });
    this_thread::sleep_for(std::chrono::seconds(2));
    getchar();
    pool.Stop();
    td1.join();
    td2.join();
}

int main() {
    // TestSyncQueue();
    TestThreadPool();
}