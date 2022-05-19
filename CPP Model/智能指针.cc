//
// Created by Jacky on 2022/5/18.
//

// 智能指针模版实现
// 取指针为原子操作，故智能指针计数线程安全
template<typename T>
class SharedPtr {
public:
    SharedPtr() : t_(nullptr), count_(nullptr) {}

    explicit SharedPtr(T *t) : t_(t), count_(nullptr) {
        if (t_ != nullptr) {
            count_ = new int(1);
        }
    }

    SharedPtr(const SharedPtr &rhs) {
        t_ = rhs.t_;
        count_ = rhs.count_;
        if (count_) {
            (*count_)++;
        }
    }

    ~SharedPtr() {
        reset();
    }

    SharedPtr &operator=(const SharedPtr &rhs) {
        if (this == &rhs) {
            return *this;
        }
        reset();
        t_ = rhs.t_;
        count_ = rhs.count_;
        if (count_ != nullptr) {
            (*count_)++;
        }
        return *this;
    }

    T &operator*() const {
        return *t_;
    }

    T *operator->() const {
        return t_;
    }

    T *get() const {
        return t_;
    }

    int count() const {
        return count_ ? *count_ : 0;
    }

    void reset() {
        if (count_ != nullptr) {
            (*count_)--;
            if ((*count_) == 0) {
                delete count_;
                delete t_;
            }
        }
    }

private:
    int *count_;
    T *t_;
};

class MyClass {
public:
    int a_, b_;

    explicit MyClass() : a_(0), b_(0) {}

    explicit MyClass(int a, int b) : a_(a), b_(b) {}
};

#include <iostream>
#include <cassert>

using namespace std;

int main() {
    MyClass *s = new MyClass(1, 2);
    s->a_ = 10, s->b_ = 20;
    SharedPtr<MyClass> sp(s);
    assert(sp->a_ == 10);
    assert(sp->b_ == 20);
    assert((*sp).a_ == 10);
    assert(sp.get() == s);
    assert(sp.count() == 1);
    SharedPtr<MyClass> sp2(sp);
    assert(sp2.count() == 2);
    {
        SharedPtr<MyClass> sp3 = sp;
        assert(sp3.count() == 3);
    }
    assert(sp.count() == 2);
    cout << "Test Succeed!" << endl;
}