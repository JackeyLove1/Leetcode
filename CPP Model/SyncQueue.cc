// simple SyncQueue Implement
// using condition_variable_any
#include <condition_variable>
#include <mutex>
#include <list>
#include <iostream>
#include <queue>

namespace one_ {
    template<typename T>
    class SyncQueue {
    private:
        mutable std::mutex mutex_;
        std::condition_variable_any not_full_;
        std::condition_variable_any not_empty_;
        std::list<T> queue_;
        int maxSize_;

    private:
        bool IsFull() const { return queue_.size() == maxSize_; }

        bool IsEmpty() const { return queue_.empty(); }

        size_t count() const { return queue_.size(); }

    public:

        SyncQueue(int init_size) : maxSize_(init_size) {}

        void Put(const T &x) {
            std::lock_guard locker(mutex_);
            while (IsFull()) {
                std::cout << "queue is full ... " << std::endl;
                not_full_.wait(mutex_);
            }
            queue_.push_back(x);
            not_empty_.notify_one();
        }

        void Take(T &x) {
            std::lock_guard locker(mutex_);
            while (IsEmpty()) {
                std::cout << "queue is empty ... " << std::endl;
                not_empty_.wait(mutex_);
            }
            x = queue_.front();
            queue_.pop_front();
            not_full_.notify_one();
        }

        bool Empty() const {
            std::lock_guard locker(mutex_);
            return IsEmpty();
        }

        bool Full() const {
            std::lock_guard locker(mutex_);
            return IsFull();
        }

        size_t Size() const {
            std::lock_guard locker(mutex_);
            return count();
        }


    };
}

namespace two_ {
    template<typename T>
    class SyncQueue {
    private:
        std::queue<T> queue_;
        mutable std::mutex mutex_;
        std::condition_variable cond_;

    public:
        SyncQueue() = default;

        void Put(T &x) {
            std::lock_guard lk(mutex_);
            queue_.emplace(x);
            cond_.notify_one();
        }

        void Take(T &x) {
            std::unique_lock lk(mutex_);
            cond_.wait(lk, [this]() { return !queue_.empty(); });
            x = queue_.front();
            queue_.pop();
        }

        bool Empty() {
            std::lock_guard lk(mutex_);
            return queue_.empty();
        }

        size_t Size() {
            std::lock_guard lk(mutex_);
            return queue_.size();
        }
    };
}