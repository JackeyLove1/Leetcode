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

inline int _count(int state) {
    return __builtin_popcount(state);
}

class Solution {
private:
    // Union Set
    static constexpr int N = 1e5 + 10;
    int e[N], ne[N], h[N], idx = 0;
    int d[N];

    inline void add(int a, int b) {
        e[idx] = b, ne[idx] = h[a], h[a] = idx++;
        d[b]++;
    }

public:
    vector<int> findSmallestSetOfVertices(int n, vector<vector<int>> &edges) {
        for (const auto &edge : edges) {
            add(edge[0], edge[1]);
        }
        vector<int> res;
        for (int i = 0; i < n; ++i) {
            if (!d[i]) res.push_back(i);
        }
        return res;
    }
};
