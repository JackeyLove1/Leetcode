

#include <stdexcept>

template<typename T>
class Singleton {
public:
    template<typename... Args>
    static T *Instance(Args &&... args) {
        if (m_instance == nullptr) {
            m_instance = new T(std::forward<Args>(args) ...);
        }
        return m_instance;
    }

    static T *GetInstance() {
        if (m_instance == nullptr) {
            throw std::logic_error("the instance is not init ... ");
        }
        return m_instance;
    }

    static void Destroy() {
        delete m_instance;
        m_instance = nullptr;
    }

private:

    Singleton() = default;

    ~Singleton() = delete;

    Singleton(const Singleton &) = delete;

    Singleton &operator=(const Singleton &) = delete;

private:
    static T *m_instance = nullptr;
};

