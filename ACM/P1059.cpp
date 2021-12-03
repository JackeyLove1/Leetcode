#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <unordered_map>
#include <map>
#include <bitset>
#include <queue>
#include <deque>
#include <unordered_set>
#include <cmath>
#include <set>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

using ll = long long;

inline int cnt(int x) {
    return __builtin_popcount(x);
}

struct Node {
    int a, b, g, k;

    Node(int _a, int _b, int _g, int _k)
            : a(_a), b(_b), g(_g), k(_k) {}
};

constexpr int N = 1e5 + 100;
int n;

int main() {
    int n, x;
    cin >> n;
    int sum(0), bus[1002] = {0};
    for (int i = 1; i <= n; i++) {
        cin >> x;
        if (bus[x])  //如果这个数已经出现过了，那么跳过
            continue;
        bus[x]++;  //如果没有出现，把数据放在桶里，并让总数居++
        sum++;
    }
    cout << sum << endl;
    for (int i = 1; i <= 1000; i++)
        if (bus[i])
            cout << i << ' ';
    cout << endl;
    return 0;
}