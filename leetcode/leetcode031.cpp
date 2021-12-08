class LRUCache {
    // 内存泄漏版本
private:
    struct DNode {
        int key, value;
        DNode *prev;
        DNode *next;

        explicit DNode(int key_, int value_) :
                key(key_), value(value_), prev(nullptr), next(nullptr) {}
    };

    DNode *head;
    DNode *tail;
    unordered_map<int, DNode *> m_;
    // int size_;
    int capacity_;

    // 只做节点操作，不做其他业务操作
    void removeNode(DNode *node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        node->next = nullptr;
        node->prev = nullptr;
    }

    void pushHead(DNode *node) {
        DNode *next = head->next;
        head->next = node;
        next->prev = node;
        node->next = next;
        node->prev = head;
    }

    DNode *removeOldest() {
        DNode *node = tail->prev;
        if (node == head) {
            throw std::runtime_error("removeOldest from a empty list!");
        }
        removeNode(node);
        return node;
    }

public:
    LRUCache(int capacity) {
        if (capacity == 0) {
            throw std::runtime_error("capacity cannot be 0!");
        }
        head = new DNode(-1, -1);
        tail = new DNode(-1, -1);
        head->next = tail;
        tail->prev = head;
        // size_ = 0;
        capacity_ = capacity;
    }

    int get(int key) {
        if (m_.count(key)) {
            DNode *kv = m_[key];
            removeNode(kv);
            pushHead(kv);
            return kv->value;
        }
        return -1;
    }

    void put(int key, int value) {
        if (m_.count(key)) {
            DNode *kv = m_[key];
            kv->value = value;
            removeNode(kv);
            pushHead(kv);
            return;
        }
        if (m_.size() >= capacity_) {
            DNode *old_node = removeOldest();
            m_.erase(old_node->key);
            delete old_node;
        }
        DNode *node = new DNode(key, value);
        pushHead(node);
        m_[key] = node;
        return;
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */