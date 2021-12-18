#include <unordered_map>
#include <unordered_set>
#include <map>
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>
#include <queue>
#include <set>
#include <cstring>
#include <cmath>
#include <list>

using namespace std;

template<typename T>
static inline void print(vector<T> &nums) {
    if (nums.empty()) {
        cout << " empty !" << endl;
        return;
    }
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}


class MyLinkedList {
private:
    list<int> l;
public:
    MyLinkedList() {

    }

    int get(int index) {
        if (index >= l.size() || index < 0) {
            return -1;
        }
        auto iter = l.begin();
        std::advance(iter, index);
        return *iter;
    }

    void addAtHead(int val) {
        l.push_front(val);
    }

    void addAtTail(int val) {
        l.push_back(val);
    }

    void addAtIndex(int index, int val) {
        if (index == l.size()) {
            l.push_back(val);
        } else if (index > l.size()) {
            return;
        } else if (index < 0) {
            l.push_front(val);
        } else {
            auto iter = l.begin();
            std::advance(iter, index);
            l.insert(iter, val);
        }
    }

    void deleteAtIndex(int index) {
        if (index >= 0 && index < l.size()) {
            auto iter = l.begin();
            std::advance(iter, index);
            l.erase(iter);
        }
    }
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */