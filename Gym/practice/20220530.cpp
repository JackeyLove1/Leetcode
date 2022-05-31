//
// Created by Jacky on 2022/5/28.
//

#include <limits>
#include <iostream>

using namespace std;

namespace parent {
    namespace v1 {
        void foo() {
            cout << "version 1" << endl;
        }
    }

    inline namespace v2 {
        void foo() {
            cout << "version2" << endl;
        }
    }
}

class Base {
public:
    virtual void f() {
        cout << "Base::f()" << endl;
    }
};

class Derived : public Base {
public:
    virtual void f() override {
        cout << "Derived::f()" << endl;
    }
};

class BigMemoryPool {
private:
    char *pool_;
public:
    static constexpr int PoolSize = 4096;

    BigMemoryPool() : pool_(new char[PoolSize]) {}

    ~BigMemoryPool() {
        if (pool_ != nullptr) {
            delete[] pool_;
        }
    }

    BigMemoryPool(const BigMemoryPool &other) {
        cout << "Copy Operation" << endl;
        memcpy(pool_, other.pool_, PoolSize);
    }

    BigMemoryPool(BigMemoryPool &&other) {
        cout << "Move Operation " << endl;
        pool_ = std::move(other.pool_);
        other.pool_ = nullptr;
    }

    BigMemoryPool &operator=(const BigMemoryPool &other) {
        cout << "Copy Operation" << endl;
        memcpy(pool_, other.pool_, PoolSize);
    }

};

class node {
    char c; // 4
    int i; // 4
    short s; // 4
} nd;

class Animal {
public:
    virtual void shout() = 0;
};

class Dog : public Animal {
public:
    virtual void shout() override {
        cout << "Dog Dog ... " << endl;
    }
};

class Cat : public Animal {
public:
    virtual void shout() override {
        cout << "Cat Cat ... " << endl;
    }
};

template<typename T>
void animalShout(T *t) {
    t->shout();
}

template<typename ... T>
auto sum_c(T... args) {
    return (args + ...);
}

int main() {
    cout << std::numeric_limits<long>::max() << endl;
    cout << std::numeric_limits<int>::max() << endl;
    cout << std::numeric_limits<char>::max() << endl;
    parent::foo();
    Base *d = new Derived();
    auto b = *d;
    b.f();
    cout << sizeof(nd) << endl;
    Animal *a1 = new Dog();
    Animal *a2 = new Cat();
    a1->shout();
    animalShout(a1);
    a2->shout();
    animalShout(a2);
    cout << sum_c(1, 2, 3) << endl;
    return 0;
}