#include <iostream>
#include <string>
#include <cmath>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <exception>
#include <atomic>
#include <queue>
#include <stack>
#include <algorithm>

// using namespace std;

// 使用傀儡节点的简单队列
template<typename T>
class queue {
private:
    struct node {
        std::shared_ptr<T> data;
        std::unique_ptr<node> next;
    };

    std::unique_ptr<node> head;
    node *tail;
public:
    queue() : head(new node), tail(head.get()) {}

    queue(const queue &) = delete;

    queue &operator=(const queue &) = delete;

    std::shared_ptr<T> try_pop() {
        if (head.get() == tail) {
            return std::make_shared<T>();
        }
        std::shared_ptr<T> const res(head->data);
        std::unique_ptr<node> old_head = std::move(head);
        head = std::move(old_head->next);
        return res;
    }

    void push(T new_value) {
        std::shared_ptr<T> new_data(
                std::make_shared<T>(std::move(new_value)));
        std::unique_ptr<node> p(new node);
        tail->data = new_data;
        node *const new_tail = p.get();
        tail->next = std::move(p);
        tail = new_tail;
    }
};

// 使用细粒度锁的线程安全的队列
template<typename T>
class threadsafe_queue {
private:
    struct node {
        std::shared_ptr<T> data;
        std::unique_ptr<node> next;
    };

    std::mutex head_mutex;
    std::mutex tail_mutex;
    std::unique_ptr<node> head;
    node *tail;

    node *get_tail() {
        std::lock_guard<std::mutex> lk(tail_mutex);
        return tail;
    }

    std::unique_ptr<node> pop_head() {
        std::lock_guard<std::mutex> head_lock(head_mutex);
        if (head.get() == get_tail()) {
            return nullptr;
        }
        std::unique_ptr<node> old_node = std::move(head);
        head = std::move(old_node->next);
        return old_node;
    }

public:
    threadsafe_queue() : head(new node), tail(head.get()) {}

    threadsafe_queue(const threadsafe_queue &) = delete;

    threadsafe_queue &operator=(const threadsafe_queue &) = delete;

    std::shared_ptr<T> try_pop() {
        std::unique_ptr<node> old_head = pop_head();
        return old_head ? old_head->data : std::make_shared<T>();
    }

    void push(T new_value) {
        std::shared_ptr<T> new_data(
                std::make_shared<T>(std::move(new_value)));
        std::unique_ptr<node> p(new node);
        node *const new_tail = p.get();
        std::lock_guard<std::mutex> lk(tail_mutex);
        tail->data = new_data;
        tail->next = std::move(p);
        tail = new_tail;
    }
};

// 支持迭代的线程安全链表
template<typename T>
class threadsafe_list {
    struct node {
        std::mutex m;
        std::shared_ptr<T> data;
        std::unique_ptr<node> next;

        node() : next() {}

        node(const T &value) : data(std::make_shared<T>(value)) {}

    };

    node head;

public:
    threadsafe_list() {}

    ~threadsafe_list() {

    }

    threadsafe_list(const threadsafe_list &) = delete;

    threadsafe_list &operator=(const threadsafe_list &) = delete;

    void push_front(const T &value) {
        std::unique_ptr<node> new_node(new node(value));
        std::lock_guard<std::mutex> lk(head.m);
        new_node->next = std::move(head.next);
        head.next = std::move(new_node);
    }

    template<typename Function>
    void for_each(Function f) {
        node *current = head;
        std::unique_lock<std::mutex> lk(head.m);
        while (node *const next = current->next.get()) {
            std::unique_lock<std::mutex> next_lk(next->m);
            lk.unlock();
            f(*next->data);
            current = next;
            lk = std::move(next_lk);
        }
    }

};

// 无锁stack
template<typename T>
class lock_free_stack {
private:
    struct node {
        std::shared_ptr<T> data;
        node *next;

        node(const T &data_) : data(std::make_shared<T>(data_)) {}
    };

    std::atomic<node *> head;
public:
    void push(const T &data) {
        node *const new_node = new node(data);
        new_node->next = head.load();
        while (!head.compare_exchange_weak(new_node->next, new_node,
                                           std::memory_order_release, std::memory_order_release));
    }

    std::shared_ptr<T> pop() {
        node *old_head = head.load();
        // 需要检查是不是一个空指针，然后再pop
        while (old_head && !head.compare_exchange_weak(old_head, old_head->next));
        return old_head ? old_head->data : std::make_shared<T>();
    }
};

// 简单的无锁队列
template<typename T>
class lock_free_queue {
private:
    struct node {
        std::shared_ptr<T> data;
        node *next;

        node() : next(nullptr) {}
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
    lock_free_queue() : head(new node), tail(head.load()) {}

    lock_free_queue(const lock_free_queue &) = delete;

    lock_free_queue &operator=(const lock_free_queue &) = delete;

    ~lock_free_queue() {
        while (node *const old_head = head.load()) {
            head.store(old_head->next);
            delete old_head;
        }
    }

    std::shared_ptr<T> pop() {
        node *old_head = pop_head();
        if (!old_head) {
            return std::shared_ptr<T>();
        }
        std::shared_ptr<T> const res(old_head->data);
        delete old_head;
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

#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_

#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <functional>
#include <vector>
#include <queue>

class ThreadPool
{
public:
    using Task = std::function<void()>;

    explicit ThreadPool(int num): _thread_num(num), _is_running(false)
    {}

    ~ThreadPool()
    {
        if (_is_running)
            stop();
    }

    void start()
    {
        _is_running = true;

        // start threads
        for (int i = 0; i < _thread_num; i++)
            _threads.emplace_back(std::thread(&ThreadPool::work, this));
    }

    void stop()
    {
        {
            // stop thread pool, should notify all threads to wake
            std::unique_lock<std::mutex> lk(_mtx);
            _is_running = false;
            _cond.notify_all(); // must do this to avoid thread block
        }

        // terminate every thread job
        for (std::thread& t : _threads)
        {
            if (t.joinable())
                t.join();
        }
    }

    void appendTask(const Task& task)
    {
        if (_is_running)
        {
            std::unique_lock<std::mutex> lk(_mtx);
            _tasks.push(task);
            _cond.notify_one(); // wake a thread to to the task
        }
    }

private:
    void work()
    {
        printf("begin work thread: %d\n", std::this_thread::get_id());

        // every thread will compete to pick up task from the queue to do the task
        while (_is_running)
        {
            Task task;
            {
                std::unique_lock<std::mutex> lk(_mtx);
                if (!_tasks.empty())
                {
                    // if tasks not empty,
                    // must finish the task whether thread pool is running or not
                    task = _tasks.front();
                    _tasks.pop(); // remove the task
                }
                else if (_is_running && _tasks.empty())
                    _cond.wait(lk);
            }

            if (task)
                task(); // do the task
        }

        printf("end work thread: %d\n", std::this_thread::get_id());
    }

public:
    // disable copy and assign construct
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool& other) = delete;

private:
    std::atomic_bool _is_running; // thread pool manager status
    std::mutex _mtx;
    std::condition_variable _cond;
    int _thread_num;
    std::vector<std::thread> _threads;
    std::queue<Task> _tasks;
};


#endif // !_THREAD_POOL_H_

#pragma once
#include<iostream>
#include<atomic>
#include<thread>
#include<assert.h>

//保证T应当是trival
//基于链表的无界无锁队列
template<typename T>
class LockFreeLinkedQueue {
public:
    //保证初始化在单线程下完成
    LockFreeLinkedQueue() {
        Node* node = new Node(Empty);
        head.store(node);
        tail.store(node);
        islockfree = node->val.is_lock_free();
    }
    ~LockFreeLinkedQueue() {
        T val = Empty;
        while (tryPop(val));
        Node* node = head.load();
        if (node != NULL)
            delete node;
    }
    bool is_lock_free() {
        return islockfree;
    }

    bool isEmpty() { return count.load() == 0; }
    bool isFull() { return false; }

    //push操作，CAS加tail锁
    bool push(T val);

    //pop操作，CAS加head锁
    bool tryPop(T& val);

    //不建议使用，当队列中无元素时，会自旋
    T pop();

private:
    struct Node {
        std::atomic<T> val;
        std::atomic<Node*>next = NULL;
        Node(T val) :val(val) {

        }
    };
    const T Empty = 0;
    std::atomic<int>count = { 0 };  //计数器
    std::atomic<Node*>head;  //头结点
    std::atomic<Node*>tail;   //尾结点
    bool islockfree;
};


//push操作，CAS加tail锁
template<typename T>
bool LockFreeLinkedQueue<T>::push(T val) {
    Node* t = NULL;
    Node* node = new Node(val);
    while (true) {
        //t==NULL，表示tail锁被抢
        if (t == NULL) {
            t = tail.load();
            continue;
        }
        //尝试加tail锁
        if (!tail.compare_exchange_weak(t, NULL))
            continue;
        break;
    }
    t->next.store(node);
    ++count;
    Node* expected = NULL;
    //释放tail锁
    bool flag = tail.compare_exchange_weak(expected, t->next);
    assert(flag);
    return true;
}

//pop操作，CAS加head锁
template<typename T>
bool LockFreeLinkedQueue<T>::tryPop(T& val) {
    Node* h = NULL, * h_next = NULL;
    while (true) {
        //h==NULL，表示head锁被抢
        if (h == NULL) {
            h = head.load();
            continue;
        }
        //尝试加head锁
        if (!head.compare_exchange_weak(h, NULL))
            continue;
        h_next = h->next.load();
        //h->next != NULL 且 count == 0
        //   此时在push函数中数据以及count计数器没有来得及更新，因此进行自旋
        if (h_next != NULL) {
            while (count.load() == 0)
                std::this_thread::yield();  //???
        }
        break;
    }
    Node* expected = NULL;
    Node* desired = h;
    //当h_next==NULL时
    //   表示当前链表为空
    if (h_next != NULL) {
        val = h_next->val;
        delete h;
        desired = h_next;
        --count;
    }
    //CAS head，释放head锁
    bool flag = head.compare_exchange_weak(expected, desired);
    assert(flag);
    return h_next != NULL;
}

//不建议使用，当队列中无元素时，会自旋
template<typename T>
T LockFreeLinkedQueue<T>::pop() {
    Node* h = NULL, * h_next = NULL;
    while (true) {
        //h==NULL，表示head锁被抢
        if (h == NULL) {
            h = head.load();
            continue;
        }
        //尝试加head锁
        if (!head.compare_exchange_weak(h, NULL))
            continue;
        h_next = h->next.load();
        //h->next == NULL
        //   当前队列为空，是否需要解head锁？
        //h->next != NULL 且 count == 0
        //   此时在push函数中数据以及count计数器没有来得及更新，因此进行自旋
        while (h_next == NULL || count.load() == 0) {
            std::this_thread::yield();  //???
            if (h_next == NULL)
                h_next = h->next.load();
        }
        break;
    }
    T val = h_next->val;
    delete h;
    --count;
    Node* expected = NULL;
    Node* desired = h_next;
    //CAS head，释放head锁
    bool flag = head.compare_exchange_weak(expected, desired);
    assert(flag);
    return val;
}


