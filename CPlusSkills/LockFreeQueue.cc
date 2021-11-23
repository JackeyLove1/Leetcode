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

template<typename T>
class LockFreeQueue {
private:
    struct node {
        std::shared_ptr<T> data;
        node *next;

        node() : next(nullptr) {
        }
    };

    std::atomic<node *> head;
    std::atomic<node *> tail;

    node *pop_head() {
        node *const old_head = head.load();
        if (old_head == tail.load()) {
            return nullptr;
        }
        head.store(old_head->next);
        return old_head;
    }

public:
    LockFreeQueue() : head(new node), tail(head.load()) {}

    LockFreeQueue(const LockFreeQueue &) = delete;

    LockFreeQueue &operator=(const LockFreeQueue &) = delete;

    ~LockFreeQueue() {
        while (node *const old_head = head.load()) {
            head.store(old_head->next);
            delete old_head;
        }
    }

    std::shared_ptr<T> pop() {
        node *old_head = pop_head();
        if (old_head == nullptr) {
            return std::shared_ptr<T>();
        }
        std::shared_ptr<T> const res(old_head->data);
        return res;
    }

    void push(T new_value) {
        std::shared_ptr<T> new_data(std::make_shared<T>(new_value));
        node *p = new node;
        node *const old_tail = tail.load();
        old_tail->data.swap(new_data);
        old_tail->next = p;
        tail.store(p);
    }
};

void PushThreadFunc(LockFreeQueue<int> &lq) {
    static thread_local int i = 1;
    std::random_device r;
    std::default_random_engine e(r());
    std::uniform_int_distribution<int> uniform_dist(1, 3);
    while (1) {
        std::cout << "PushThreadFuncID: " << std::this_thread::get_id() << " value: " << i << std::endl;
        lq.push(i++);
        std::this_thread::sleep_for(std::chrono::seconds(uniform_dist(e)));
    }
}

void GetThreadFunc(LockFreeQueue<int> &lq) {
    while (1) {
        auto res = lq.pop();
        if (res.get() != nullptr) {
            std::cout << "GetThreadFuncID: " << std::this_thread::get_id() << " value: " << *res << std::endl;
        }
    }
}

int main() {
    LockFreeQueue<int> q;
    std::thread t1(PushThreadFunc, std::ref(q));
    std::thread t2(GetThreadFunc, std::ref(q));
    t1.join();
    t2.join();
    return 0;
}