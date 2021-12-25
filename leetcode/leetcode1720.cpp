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
#include <atomic>

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

class MedianFinder {
private:
    priority_queue<int, vector<int>, greater<>> min_heap;
    priority_queue<int, vector<int>, less<>> max_heap;
public:
    /** initialize your data structure here. */
    MedianFinder() {

    }

    void addNum(int num) {
        max_heap.push(num);
        min_heap.push(max_heap.top());
        max_heap.pop();
        if (max_heap.size() > min_heap.size()) {
            max_heap.push(min_heap.top());
            min_heap.pop();
        }
    }

    double findMedian() {
        if (min_heap.size() == max_heap.size()) {
            return (static_cast<double>(min_heap.top()) + max_heap.top()) / 2;
        }
        return static_cast<double>(max_heap.top());
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */

int main() {

}