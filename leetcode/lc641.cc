#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <cmath>
#include <unordered_map>
#include <unordered_set>


using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

using ull = unsigned long long;
using ll = long long;
using PII = pair<int, int>;

constexpr int N = 2010, M = 4000010;

class MyCircularDeque {
private:
    deque<int> d;
    int cap;
public:
    explicit MyCircularDeque(int k) : cap{k} {

    }

    bool insertFront(int value) {
        if (d.size() == cap) {
            return false;
        }
        d.push_front(value);
        return true;
    }

    bool insertLast(int value) {
        if (d.size() == cap) {
            return false;
        }
        d.push_back(value);
        return true;
    }

    bool deleteFront() {
        if (d.empty()) {
            return false;
        }
        d.pop_front();
        return true;
    }

    bool deleteLast() {
        if (d.empty()) {
            return false;
        }
        d.pop_back();
        return true;
    }

    int getFront() {
        if (d.empty()) {
            return -1;
        }
        return d.front();
    }

    int getRear() {
        if (d.empty()) {
            return -1;
        }
        return d.back();
    }

    bool isEmpty() {
        return d.empty();
    }

    bool isFull() {
        return d.size() == cap;
    }
};

/**
 * Your MyCircularDeque object will be instantiated and called as such:
 * MyCircularDeque* obj = new MyCircularDeque(k);
 * bool param_1 = obj->insertFront(value);
 * bool param_2 = obj->insertLast(value);
 * bool param_3 = obj->deleteFront();
 * bool param_4 = obj->deleteLast();
 * int param_5 = obj->getFront();
 * int param_6 = obj->getRear();
 * bool param_7 = obj->isEmpty();
 * bool param_8 = obj->isFull();
 */