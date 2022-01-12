#include <unordered_map>
#include <unordered_set>
#include <map>
#include <iostream>
#include <utility>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>
#include <queue>
#include <set>
#include <tuple>
#include <list>
#include <atomic>
#include <thread>

#include <cstring>
#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

template<typename T>
static inline void print(const vector<T> &nums) {
    if (nums.empty()) {
        cout << " empty !" << endl;
        return;
    }
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

inline int count(int state) {
    return __builtin_popcount(state);
}

class CustomStack {
private:
    vector<int> vec;
    int sz_;
public:
    CustomStack(int maxSize) : sz_(maxSize) {
        vec.reserve(maxSize);
    }

    void push(int x) {
        if (vec.size() < sz_) {
            vec.push_back(x);
        }
    }

    int pop() {
        if(vec.empty()){
            return -1;
        }
        int top = vec.back();
        vec.pop_back();
        return top;
    }

    void increment(int k, int val) {
        if (vec.size() <= k) {
            for (int i = 0; i < vec.size(); ++i) {
                vec[i] += val;
            }
            return;
        }
        for (int i = 0; i < k; ++i) {
            vec[i] += val;
        }
    }
};

/**
 * Your CustomStack object will be instantiated and called as such:
 * CustomStack* obj = new CustomStack(maxSize);
 * obj->push(x);
 * int param_2 = obj->pop();
 * obj->increment(k,val);
 */