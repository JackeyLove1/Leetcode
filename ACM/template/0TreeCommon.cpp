#include <iostream>
#include <algorithm>

using namespace std;

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

inline int count(int state) {
    return __builtin_popcount(state);
}

constexpr int N = 1e3 + 100;
int e[N], ne[N], w[N], h[N], idx;

inline void init() {
    memset(h, -1, sizeof h);
}

inline void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
