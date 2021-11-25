#include <iostream>
#include <functional>
#include <tuple>
#include <set>
#include <cmath>
#include <memory>
#include <any>
#include <atomic>
#include <random>
#include <chrono>
#include <thread>
#include <vector>

template<typename T>
class ThreadSafeList {
private:
    struct node {
        std::mutex m_;
        std::shared_ptr<T> data_;
        std::unique_ptr<node> next_;

        node() : next_() {}

        node(const T &value) : data_(std::make_shared<T>(value)) {}
    };

    node head;

public:
    ThreadSafeList() = default;

    ThreadSafeList(const ThreadSafeList &) = delete;

    ThreadSafeList &operator=(const ThreadSafeList &) = delete;

    void push_front(const T &value) {
        std::unique_ptr<node> new_node(new node(value));
        std::lock_guard lk(head.m_);
        new_node->next_ = std::move(head.next_);
        head.next_ = std::move(new_node);
    }

    template<typename Function>
    void for_each(Function f) {
        node *current = &head;
        std::unique_lock lk(head.m_);
        while (node *const next = current->next_.get()) {
            std::unique_lock next_lk(next->m_);
            lk.unlock();
            f(*next->data_);
            current = next;
            lk = std::move(next_lk);
        }
    }

    template<typename Predicate>
    std::shared_ptr<T> find_first_if(Predicate p) {
        node *current = &head;
        std::unique_lock lk(head.m_);
        while (node *const next = current->next_.get()) {
            std::unique_lock next_lk(next->m_);
            lk.unlock();
            if (p(*next->data_)) {
                return next->data_;
            }
            current = next;
            lk = std::move(next_lk);
        }
        return std::shared_ptr<T>();
    }

    template<typename Predicate>
    void remove_if(Predicate p) {
        node *current = &head;
        std::unique_lock lk(head.m_);
        while (node *const next = current->next.get()) {
            std::unique_lock next_lk(next->m_);
            if (p(*next->data_)) {
                std::unique_ptr<node> old_next = std::move(current->next_);
                current->next_ = std::move(next->next_);
                next_lk.unlock();
            } else {
                lk.unlock();
                current = next;
                lk = std::move(next_lk);
            }
        }
    }

};

int main() {
    ThreadSafeList<int> l;
    l.push_front(1);
    l.for_each([](const int &item) {
        std::cout << item << " ";
    });
    std::cout << std::endl;

}