#include <iostream>
#include <shared_mutex>
#include <mutex>
#include <fstream>
#include <cmath>
#include <cstring>
#include <thread>
#include <pthread.h>

namespace C11 {
    static std::once_flag once_control;
    template<typename T>
    class Singleton {
    public:
    // 可以使用unique_ptr<>()
        static T *getInstance() {
            std::call_once(once_control, Singleton::init);
            return value_;
        }

        static void destroy() {
            if (nullptr != value_) {
                delete value_;
            }
        }

    private:
        Singleton() = delete;

        ~Singleton() = delete;

        Singleton(const Singleton &) = delete;

        Singleton &operator=(const Singleton &) = delete;

        static void init() {
            value_ = new T();
            ::atexit(destroy);
        }

        static T *value_;
    
    };

    template<typename T> T *Singleton<T>::value_ = nullptr;
}

namespace C03 {
    template<typename T>
    class Singleton {
    public:
        static T *getInstance() {
            pthread_once(&once_control, &Singleton::init);
            return value_;
        }

        static void destroy() {
            if (nullptr != value_) {
                delete value_;
            }
        }

    private:
        Singleton();

        ~Singleton();

        static void init() {
            value_ = new T();
            ::atexit(destroy);
        }

        static T *value_;
        static pthread_once_t once_control;
    };

    template<typename T>
    pthread_once_t Singleton<T>::once_control = PTHREAD_ONCE_INIT;

    template<typename T> T *Singleton<T>::value_ = nullptr;

}