// Author: Jacky
// Time: 2021-09-25
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
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t; });
    cout << endl;
}

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

constexpr int N = 1010;
using PII = pair<int, int>;
PII p[N];

// a, c from little to high
inline vector<int> mul(vector<int> &a, int b) {
    vector<int> c;
    int t = 0;
    for (int i = 0; i < a.size(); ++i) {
        t += a[i] * b;
        c.push_back(t % 10);
        t /= 10;
    }
    while (t) {
        c.push_back(t % 10);
        t /= 10;
    }
    return c;
}

inline vector<int> div(vector<int> &a, int b) {
    vector<int> c;
    for (int i = a.size() - 1, t = 0; i >= 0; --i) {
        t = t * 10 + a[i];
        c.push_back(int(t / b));
        t = t % b;
    }
    reverse(c.begin(), c.end());
    while (!c.empty() && c.back() == 0) {
        c.pop_back();
    }
    return c;
}

inline vector<int> max_vec(vector<int> a, vector<int> b) {
    if (a.size() > b.size()) return a;
    if (a.size() < b.size()) return b;
    if (vector<int>(a.rbegin(), a.rend()) > vector<int>(b.rbegin(), b.rend())) return a;
    return b;
}

int n;

int main() {
    fhj();
    cin >> n;
    for (int i = 0; i <= n; ++i) {
        int a, b;
        cin >> a >> b;
        p[i] = {a * b, a};
    }
    sort(p + 1, p + n + 1);
    vector<int> product(1, 1);
    vector<int> res(1, 0);
    for (int i = 0; i <= n; ++i) {
        if (i) res = max_vec(res, div(product, p[i].first / p[i].second));
        product = mul(product, p[i].second);
    }
    for (int i = res.size() - 1; i >= 0; --i) {
        cout << res[i];
    }
    cout << endl;
    return 0;
}