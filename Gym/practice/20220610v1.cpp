#include <iostream>
#include <limits>
#include <stdlib.h>
#include <cinttypes>
#include <stdlib.h>
#include <unistd.h>
#include <vector>


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

int main() {
    std::vector<int, MyAllocator<int>> v(0);
    for (size_t i = 0; i < 10; i++) {
        sleep(1);
        v.push_back(i);
        std::cout << "当前容器内存占用量:" << v.get_allocator().get_allocations() << std::endl;
    }
}