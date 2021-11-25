template<class T>
class slist {
    struct Node {
        T t;
        std::shared_ptr<Node> next;
    };
    std::atomic<std::shared_ptr<Node>> head;
public:
    class reference {
        std::shared_ptr<Node> p;
    public:
        reference(std::shared_ptr<Node> p_) {}

        T &operator*() { return p->t; }

        T *operator->() { return &p->t; }
    };

    auto find(T t) const {
        auto p = head.load();
        while (p && p->t != t) {
            p = p->next;
        }
        return reference(move(p));
    }

    void push_front(T t) {
        auto p = std::make_shared<Node>();
        p->t = t;
        p->next = head;
        while (!head.compare_exchange_weak(p->next, p)) {}
    }

    auto pop_front() {
        auto p = head.load();
        while (p && !head.compare_exchange_weak(p, p->next)) { ; }
        return reference(std::move(p));
    }
};