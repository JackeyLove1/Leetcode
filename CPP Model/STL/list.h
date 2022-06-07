#pragma once

#include <stdexcept>
#include <iostream>

template<typename T>
class list;

template<typename N>
class list_iterator {
private:
    N *pos;

    template<typename T> friend
    class list;

public:
    using value_type = typename N::value_type;
    using reference_type = typename N::reference_type;
    using const_reference_type = typename N::const_reference_type;
    using self_type = list_iterator<N>;

    list_iterator() noexcept: pos(nullptr) {}

    list_iterator(N *pos_) noexcept: pos(pos_) {}

    bool operator!=(self_type const &rhs) const {
        return pos != rhs.pos;
    }

    bool operator==(self_type const &rhs) const {
        return pos == rhs.pos;
    }

    self_type &operator++() {
        if (pos) pos = pos->next;
        return *this;
    }

    reference_type operator*() {
        if (pos == nullptr) {
            throw "Dereferencing Nullptr!";
        }
        if (pos) return pos->value;
    }
};

template<typename T>
class list_node {
public:
    using value_type = T;
    using reference_type = T &;
    using const_reference_type = const T &;

    T value;
    list_node *prev;
    list_node *next;

    list_node(T const &value_, list_node *prev_, list_node *next_) :
            value(value_), prev(prev_), next(next_) {}
};

template<typename T>
class list {
private:
    using node_type = list_node<T>;
    node_type *head;
public:
    using value_type = T;
    using iterator = list_iterator<node_type>;

    list() : head() {}

    ~list() {
        while (head) {
            node_type *tmp = head;
            head = head->next;
            delete tmp;
        }
    }

    void push_front(T const &v) {
        head = new node_type(v, nullptr, head);
        if (head->next) head->next->prev = head;
    }

    void pop_front(T const &v) {
        if (head) {
            node_type *h = head;
            head = head->next;
            head->prev = nullptr;
            delete h;
        }
    }

    bool is_empty() const {
        return head == nullptr;
    }

    iterator begin() {
        return iterator(head);
    }

    iterator end() {
        return iterator();
    }
};


int main() {
    using std::cout, std::endl;
    list<int> l;
    l.push_front(1);
    l.push_front(2);
    l.push_front(3);
    for (auto iter = l.begin(); iter != l.end(); ++iter) {
        cout << (*iter) << endl;
    }
    return 0;
}