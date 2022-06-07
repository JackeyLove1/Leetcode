//
// Created by Jacky on 2022/6/7.
//
// simple object pool
#include <list>

template<typename Object>
class ObjectPool {
public:
    explicit ObjectPool(size_t size_) : m_size(size_) {
        for (int i = 0; i < m_size; ++i) {
            m_pool.push_back(new Object());
        }
    }

    ~ObjectPool() {
        for (auto it = m_pool.begin(); it != m_pool.end();) {
            delete (*it);
            ++it;
        }
        m_size = 0;
    }

    Object *GetObject() {
        Object *pObj = nullptr;
        if (m_size == 0) {
            pObj = new Object();
        } else {
            pObj = m_pool.front();
            m_pool.pop_front();
            --m_size;
        }
        return pObj;
    }

    void ReturnObject(Object *obj) {
        m_pool.push_back(obj);
        ++m_size;
    }

private:
    size_t m_size;
    std::list<Object *> m_pool;
};

#include <iostream>

using std::cout, std::endl;

class A {
public:
    A() {
        cout << "Create Object A" << endl;
    }

    ~A() {
        cout << "Destory Object A" << endl;
    }
};

int main() {
    ObjectPool<A> object_pool(10);
    auto *obj = object_pool.GetObject();
    object_pool.ReturnObject(obj);
    return 0;
}