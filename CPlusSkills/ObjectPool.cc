#include <iostream>
#include <string>
#include <memory>
#include <map>

// using namespace std;

class NoCopyable {
protected:
    NoCopyable() = default;

    ~NoCopyable() = default;

    NoCopyable(const NoCopyable &) = delete;

    NoCopyable &operator=(const NoCopyable &) = delete;
};

// ObjectPool Implement
constexpr int MaxObjectNum = 10;

template<typename T>
class ObjectPool : public NoCopyable {
public:
    template<typename ... Args>
    using Constructor = std::function<std::shared_ptr<T>(Args...)>;


    template<typename ... Args>
    void Init(size_t num, Args &&... args) {
        // using assert ?
        if (num <= 0 || num > MaxObjectNum) {
            throw std::logic_error("object num out of range ");
        }
        auto ConstructName = typeid(Constructor<Args...>).name();
        for (size_t i = 0; i < num; ++i) {
            m_object_map.emplace(ConstructName, std::shared_ptr<T>(
                    new T(std::forward<Args>(args) ...),
                    [this, ConstructName](T *p) {
                        m_object_map.emplace(ConstructName,
                                             std::shared_ptr<T>(p));
                    }
            ));
        }
    }

    template<typename ... Args>
    std::shared_ptr<T> Get() {
        std::string constructName = typeid(Constructor<Args...>).name();
        auto range = m_object_map.equal_range(constructName);
        for (auto it = range.first; it != range.second; ++it) {
            auto ptr = it->second;
            m_object_map.erase(it);
            return ptr;
        }
        return nullptr;
    }

private:
    std::multimap<std::string, std::shared_ptr<T>> m_object_map;
    bool needClear;
};

#include <iostream>

using namespace std;

struct test {
    test() = default;

    test(int a) {}

    test(const int &a, const int &b) {}

    void print(const string &str) {
        cout << str << endl;
    }

};

void print(const shared_ptr<test> &p, const string &str) {
    if (p != nullptr) {
        p->print(str);
    }
}

int main() {
    ObjectPool<test> pool;
    pool.Init(2);
    {
        auto p = pool.Get();
        print(p, "p");
        auto p2 = pool.Get();
        print(p2, "p2");
    }
    auto p = pool.Get();
    print(p, "p");
    auto p2 = pool.Get();
    print(p2, "p2");

    pool.Init(2, 1);
    auto p4 = pool.Get<int>();
    print(p4, "p4");
    pool.Init(2, 1, 1);
    auto p5 = pool.Get<int, int>();
    print(p5, "p5");
}