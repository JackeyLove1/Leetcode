#include <iostream>
#include <limits>
#include <stdlib.h>
#include <cinttypes>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <string>
#include <memory>
#include <stack>

// self-designed memory allocate
template<class T>
class MyAllocator {
public:
    using value_type = T;
    using pointer = T *;
    using const_pointer = const T *;

    using void_pointer = void *;
    using const_void_pointer = const void *;

    using size_type = size_t;
    using difference = std::ptrdiff_t;

    template<class U>
    struct rebind {
        using other = MyAllocator<U>;
    };

    MyAllocator() = default;

    ~MyAllocator() = default;

    //分配内存
    pointer allocate(size_type numObjects) {
        std::cout << "Allocate " << numObjects << " Objects\n";
        allocCount += numObjects;
        return static_cast<pointer>(operator new(sizeof(T) * numObjects));
    }

    //分配内存
    pointer allocate(size_type numObjects, const_void_pointer hint) {
        return allocate(numObjects);
    }

    //释放内存
    void deallocate(pointer p, size_type numObjects) {
        allocCount -= numObjects;
        std::cout << "Deallocate " << numObjects << " Objects\n";
        operator delete(p);
    }

    //分配器支持最大的内存数
    size_type max_size() const {
        return std::numeric_limits<size_type>::max();
    }

    //返回每次分配/删除的内存数
    size_type get_allocations() const {
        return allocCount;
    }

private:
    //统计当前内存的使用量
    size_type allocCount;
};

// factory module
enum class EmType {
    EMP,
    MGR,
    SVR,
    TMR,
};

class Employee {
private:
    std::string name;
    int id;
public:
    std::string getName() const {
        return name;
    }

    int getId() const {
        return id;
    }

    Employee() = default;

    virtual ~Employee() {};
};

class Manager : public Employee {
public:
    Manager() {
        std::cout << "Manage ... \n";
    }

    ~Manager() {
        std::cout << "DeManage .. \n";
    }
};

class SuperVisor : public Employee {
public:
    SuperVisor() {
        std::cout << "SuperVisor ...\n";
    }

    ~SuperVisor() {
        std::cout << "DeSuperVisor ... \n";
    }
};

class Teamer : public Employee {
public:
    Teamer() {
        std::cout << "Teamer ...\n";
    }

    ~Teamer() {
        std::cout << "DeTeamer ... \n";
    }
};

class Factory1 {
private:
    std::stack<Employee *> gc;
public:
    virtual ~Factory1() {
        while (!gc.empty()) {
            Employee *emp = gc.top();
            gc.pop();
            std::cout << "销毁:" << emp << std::endl;
            delete emp;
            emp = nullptr;
        }
    }

    Employee *makeObject(EmType type) {
        switch (type) { //动态返回多态派生的典型代码
            case EmType::MGR:
                gc.push(new Manager());
                break;
            case EmType::SVR:
                gc.push(new SuperVisor());
                break;
            case EmType::TMR:
                gc.push(new Teamer());
                break;
            default:
                gc.push(new Employee());
                break;
        }
        return gc.top();
    }
};

void doSomething1() {
    Employee *em1 = new Manager();
    Employee *em2 = new SuperVisor();
    Employee *em3 = new Teamer();
    delete em1;
    delete em2;
    delete em3;
}

void doSomething2() {
    Factory1 f;
    auto *em1 = f.makeObject(EmType::MGR);
    std::cout << "create: " << static_cast<void *>(em1) << std::endl;
    auto *em2 = f.makeObject(EmType::SVR);
    std::cout << "create: " << static_cast<void *>(em2) << std::endl;
    auto *em3 = f.makeObject(EmType::TMR);
    std::cout << "create: " << static_cast<void *>(em3) << std::endl;
}


class Factory2 {
private:
    std::vector<std::shared_ptr<Employee>> gc;
public:
    ~Factory2() {
        while (!gc.empty()) {
            gc.pop_back();
        }
    }

    std::shared_ptr<Employee> makeObject(EmType type) {
        switch (type) {
            case EmType::MGR:
                gc.emplace_back(std::make_shared<Manager>());
                break;
            case EmType::SVR:
                gc.emplace_back(std::make_shared<SuperVisor>());
                break;
            case EmType::TMR:
                gc.emplace_back(std::make_shared<Teamer>());
                break;
            default:
                return nullptr;
        }
        return gc.front();
    }
};

void doSomething3() {
    Factory2 f;
    auto em1 = f.makeObject(EmType::MGR);
    std::cout << "create: " << static_cast<void *>(em1.get()) << std::endl;
    std::cout << "use count: " << em1.use_count() << std::endl;
    auto em2 = f.makeObject(EmType::SVR);
    std::cout << "create: " << static_cast<void *>(em2.get()) << std::endl;
    std::cout << "use count: " << em1.use_count() << std::endl;
    auto em3 = f.makeObject(EmType::TMR);
    std::cout << "create: " << static_cast<void *>(em3.get()) << std::endl;
    std::cout << "use count: " << em1.use_count() << std::endl;
}

int main() {
    std::vector<int, MyAllocator<int>> v(0);
    for (size_t i = 0; i < 10; i++) {
        v.push_back(i);
        std::cout << "当前容器内存占用量:" << v.get_allocator().get_allocations() << std::endl;
    }
    doSomething1();
    doSomething2();
    doSomething3();
    return 0;
}