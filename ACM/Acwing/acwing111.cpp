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
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << endl; });
    cout << endl;
}

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

constexpr int N = 1e6 + 10;

int n;

struct node {
    int l, r, idx;

    bool operator<(const node &rhs) const {
        if (r == rhs.r) {
            return l > rhs.l;
        }
        return r > rhs.r;
    }

    friend ostream &operator<<(ostream &os, const node &_node) {
        return os << "l: " << _node.l << " r: " << _node.r << " idx: " << _node.idx;
    }
};

node cows[N];
const int debug = 0;
int as[N];

int main() {
    fhj();
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> cows[i].l >> cows[i].r;
        cows[i].idx = i + 1;
    }
    sort(cows, cows + n, [](const node &n1, const node &n2) {
        if (n1.l == n2.l) {
            return n1.r < n2.r;
        }
        return n1.l < n2.l;
    });
    priority_queue<node> heap;
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        if (!heap.empty() && heap.top().r < cows[i].l) {
            as[cows[i].idx] = as[heap.top().idx];
            if (debug) cout << "top: " << heap.top() << endl;
            heap.pop();
        } else {
            ++ans;
            as[cows[i].idx] = ans;
        }
        heap.push(cows[i]);
    }
    cout << ans << endl;
    for (int i = 1; i <= n; ++i) {
        cout << as[i] << endl;
    }
    return 0;
}