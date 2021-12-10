#include <unordered_map>
#include <map>
#include <set>
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>
#include <queue>

using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

class MyQueue {
private:
    queue<int> q;
public:
    /** Initialize your data structure here. */
    MyQueue() {

    }

    /** Push element x to the back of queue. */
    void push(int x) {
        q.push(x);
    }

    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        int t = q.front();
        q.pop();
        return t;
    }

    /** Get the front element. */
    int peek() {
        return q.front();
    }

    /** Returns whether the queue is empty. */
    bool empty() {
        return q.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */