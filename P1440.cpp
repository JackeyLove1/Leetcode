#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <unordered_map>
#include <queue>

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

constexpr int N = 2e6 + 100, INF = 1e9;
int w[N];
int n, m;

int main() {
    fhj();
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> w[i];
    }
    deque<int> q; // put index of the array
    for (int i = 1; i <= n; ++i) {
        if (q.empty()) {
            cout << 0 << endl;
            q.push_back(i);
            continue;
        }
        while (!q.empty() && i - q.front() > m) {
            q.pop_front();
        }
        cout << w[q.front()] << endl;
        while (!q.empty() && w[i] <= w[q.back()]) {
            q.pop_back();
        }
        q.push_back(i);
    }
    return 0;
}