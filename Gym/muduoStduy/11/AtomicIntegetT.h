//
// Created by Jacky on 2021/11/10.
//

#ifndef STUDY_ATOMICINTEGETT_H
#define STUDY_ATOMICINTEGETT_H

#include "nocopyable.h"
#include <cstdint>
#include <atomic>

namespace Study {
    template<typename T>
    class AtomicIntegerT : public noncopyable {
    private:
        volatile T value_;
    public:
        AtomicIntegerT() : value_(0) {}

        AtomicIntegerT(T value) : value_(value) {}

        T get() {
            return __sync_val_compare_and_swap(&value_, 0, 0);
        }

        T getAndAdd(T x) {
            return __sync_fetch_and_add(&value_, x);
        }

        T addAndGet(T x) {
            return getAndAdd(x) + x;
        }

        T incrementAndGet() {
            return addAndGet(1);
        }

        T decrementAndGet() {
            return addAndGet(-1);
        }

        void add(T x) {
            getAndAdd(x);
        }

        void increment() {
            getAndAdd(1);
        }

        void decrement() {
            getAndAdd(-1);
        }

        T getAndSet(T newValue) {
            return __sync_lock_test_and_set(&value_, newValue);
        }


    };

    using AtomicInt32 = AtomicIntegerT<int32_t>;
    using AtomicInt64 = AtomicIntegerT<int64_t>;
}

namespace Study {
    template<typename T>
    class AtomicInt : public noncopyable {
    private:
        std::atomic<T> value_;
    public:
        AtomicInt() : value_(0) {
        }

        AtomicInt(T value) : value_(value) {
        }

        T get() {
            return value_.load();
        }

        T getAndAdd(int x) {
            T cur = value_.load();
            value_.fetch_add(x, std::memory_order_relaxed);
            return cur;
        }

        T addAndGet(int x) {
            value_.fetch_add(x, std::memory_order_relaxed);
            return value_.load();
        }


    };
}
#endif //STUDY_ATOMICINTEGETT_H
