#include <iostream>
#include <mutex>
#include <fstream>
#include <cstring>
#include <cmath>
#include <shared_mutex>


// implements the skiplist

constexpr bool DEBUG = true;

template<typename K, typename V>
class Node {
public:
    Node() = delete;

    explicit Node(K key, V value, int level);

    ~Node();

    K get_key() const;

    V get_value() const;

    void set_value(V);

    Node<K, V> **forward;

    int node_level;
private:
    K key_;
    V value_;
};

template<typename K, typename V>
Node<K, V>::Node(K key, V value, int level)
        :key_(key), value_(value), node_level(level) {
    forward = new Node<K, V> *[node_level + 1];
    memset(forward, 0, sizeof(Node<K, V> *) * (node_level + 1));
}

template<typename K, typename V>
Node<K, V>::~Node() {
    delete[]forward;
}

template<typename K, typename V>
K Node<K, V>::get_key() const {
    return key_;
}

template<typename K, typename V>
V Node<K, V>::get_value() const {
    return value_;
}

template<typename K, typename V>
void Node<K, V>::set_value(V value) {
    value_ = value;
}

template<typename K, typename V>
class SkipList {
public:
    SkipList(const SkipList &) = delete;

    SkipList &operator=(const SkipList &) = delete;

    SkipList() = delete;

    explicit SkipList(int);

    ~SkipList();

    int get_random_level();

    Node<K, V> *create_node(K, V, int);

    int insert_element(K, V);

    void display_list();

    bool search_element(K);

    void delete_element(K);

    void dump_file();

    void load_file();

    int size() const { return element_count_; }

private:
    mutable std::shared_mutex mutex_;

    int max_level_;

    int skip_list_level_;

    Node<K, V> *head_;

    std::ofstream file_writer_;

    std::ifstream file_reader_;

    int element_count_;
};

template<typename K, typename V>
SkipList<K, V>::SkipList(int init_level):
        max_level_(init_level), skip_list_level_(0), element_count_(0) {
    K k;
    V v;
    head_ = new Node<K, V>(k, v, init_level);
}

template<typename K, typename V>
SkipList<K, V>::~SkipList() {
    if (file_reader_.is_open()) {
        file_reader_.close();
    }
    if (file_writer_.is_open()) {
        file_writer_.close();
    }
    delete head_;
}

template<typename K, typename V>
int SkipList<K, V>::get_random_level() {
    int k = 1;
    while (rand() % 2) {
        ++k;
    }
    k = (k < max_level_) ? k : max_level_;
    return k;
}

template<typename K, typename V>
Node<K, V> *SkipList<K, V>::create_node(K k, V v, int level) {
    Node<K, V> *node = new Node<K, V>(k, v, level);
    return node;
}

template<typename K, typename V>
int SkipList<K, V>::insert_element(K key, V value) {
    std::unique_lock locker(mutex_);
    Node<K, V> *current = head_;

    Node<K, V> *update[max_level_ + 1];
    memset(update, 0, sizeof(Node<K, V> *) * (max_level_ + 1));

    for (int i = skip_list_level_; i >= 0; --i) {
        while (current->forward[i] && current->forward[i]->get_key() < key) {
            current = current->forward[i];
        }
        update[i] = current;
    }

    current = current->forward[0];

    if (current != nullptr && current->get_key() == key) {
        if (DEBUG) std::cout << "key: " << key << " exists" << std::endl;
        return 1;
    }

    if (current == nullptr || current->get_key() != key) {
        int random_level = get_random_level();
        if (random_level > skip_list_level_) {
            for (int i = skip_list_level_ + 1; i <= random_level; ++i) {
                update[i] = head_;
            }
            skip_list_level_ = random_level;
        }

        Node<K, V> *inserted_node = create_node(key, value, random_level);

        for (int i = 0; i <= random_level; ++i) {
            inserted_node->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = inserted_node;
        }
        std::cout << "Successfully insert key " << key << " value: " << value << std::endl;
        ++element_count_;
    }
    return 0;
}

template<typename K, typename V>
void SkipList<K, V>::display_list() {
    std::cout << "***** SkipList *****" << std::endl;
    for (int i = 0; i < skip_list_level_; ++i) {
        std::cout << "Level: " << i << std::endl;
        auto cur = head_->forward[i];
        while (cur != nullptr) {
            std::cout << cur->get_key() << " : " << cur->get_value() << "   ";
            cur = cur->forward[i];
        }
        std::cout << std::endl;
    }
}

template<typename K, typename V>
bool SkipList<K, V>::search_element(K key) {
    std::shared_lock<std::shared_mutex> lock(mutex_);
    if (DEBUG) {
        std::cout << "search_element--------" << std::endl;
    }

    Node<K, V> *current = head_;
    for (int i = skip_list_level_; i >= 0; --i) {
        while (current->forward[i] && current->forward[i]->get_key() < key) {
            current = current->forward[i];
        }
    }
    current = current->forward[0];

    if (current and current->get_key() == key) {
        if (DEBUG) std::cout << "find the key: " << key << " : " << " value: " << current->get_value() << std::endl;
        return true;
    }
    std::cout << "cant find the key; " << key << std::endl;
    return false;
}

template<typename K, typename V>
void SkipList<K, V>::delete_element(K) {

}

template<typename K, typename V>
void SkipList<K, V>::dump_file() {

}

template<typename K, typename V>
void SkipList<K, V>::load_file() {

}

int main() {
    SkipList<int, std::string> skl(6);
    skl.insert_element(1, "Hello");
    skl.display_list();
}