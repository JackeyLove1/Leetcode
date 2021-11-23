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
class LockFreeStack {
private:
    struct node {
        std::shared_ptr<T> data;
        std::shared_ptr<node> next;

        explicit node(T const &data_) : data(std::make_shared<T>(data_)) {}
    };

    std::shared_ptr<node> head;

public:
    void push(T const &data) {
        std::shared_ptr<node> const new_node = std::make_shared<node>(data);
        new_node->next = head;
        while (!std::atomic_compare_exchange_weak(&head, &new_node->next, new_node));
    }

    std::shared_ptr<T> pop() {
        std::shared_ptr<node> old_head = std::atomic_load(&head);
        while (old_head && !std::atomic_compare_exchange_weak(&head, &old_head, old_head->next));
        return old_head ? old_head->data : std::shared_ptr<T>();
    }
};

void PushThreadFunc(LockFreeStack<int> &lq) {
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

void GetThreadFunc(LockFreeStack<int> &lq) {
    while (1) {
        auto res = lq.pop();
        if (res.get() != nullptr) {
            std::cout << "GetThreadFuncID: " << std::this_thread::get_id() << " value: " << *res << std::endl;
        }
    }
}

int main() {
    LockFreeStack<int> q;
    std::thread t1(PushThreadFunc, std::ref(q));
    std::thread t2(GetThreadFunc, std::ref(q));
    t1.join();
    t2.join();
    return 0;
}