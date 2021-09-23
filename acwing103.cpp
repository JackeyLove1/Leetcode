// Author: Jacky
// Time: 2021-09-22
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <bitset>
#include <cstring>
#include <queue>
#include <tuple>
#include <deque>

using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

template<typename T>
inline void print(vector<vector<T>> &nums) {
    for (auto &num : nums) {
        for (auto &n : num) {
            cout << n << " ";
        }
        cout << endl;
    }
    // cout << "ending ... " << endl;
}

inline void startFunc() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

constexpr int N = 2e5 + 100;
int p[N], m1[N], m2[N];

struct movies {
    int a, b, idx;
};

int n, m;
const int debug = 0;

int main() {
    startFunc();
    cin >> n;
    unordered_map<int, int> hash;
    for (int i = 1; i <= n; ++i) {
        cin >> p[i];
        ++hash[p[i]];
    }
    cin >> m;
    for (int i = 0; i < m; ++i) {
        cin >> m1[i];
    }
    for (int i = 0; i < m; ++i) {
        cin >> m2[i];
    }
    vector<movies> movie(m);
    for (int i = 0; i < m; ++i) {
        movie[i] = {m1[i], m2[i], i + 1};
    }
    sort(movie.begin(), movie.end(), [&](const movies &t1, const movies &t2) {
        if (hash[t1.a] == hash[t2.a]) {
            return hash[t1.b] > hash[t2.b];
        }
        return hash[t1.a] > hash[t2.a];
    });
    if (debug) {
        for (auto &ms : movie) {
            cout << hash[ms.a] + hash[ms.b] << " ";
            cout << hash[ms.a] << " " << hash[ms.b] << " ";
            cout << "idx: " << ms.idx << endl;
        }
    }
    cout << movie[0].idx << endl;
    return 0;
}