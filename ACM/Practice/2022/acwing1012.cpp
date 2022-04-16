#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <cstdlib>
#include <unordered_set>
#include <cmath>
#include <numeric>
#include <cstring>
#include <queue>
#include <string>
#include <climits>

using namespace std;

template<typename T>
static inline void print(vector<T> &vec) {
    for_each(vec.begin(), vec.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

constexpr int N = 5100;
int f[N];
int l, r;

struct node {
    int l, r;

    node(int l_, int r_) : l(l_), r(r_) {}
};

vector<node> nums;
int n;

int main() {
    fhj();
    cin >> n;
    nums.reserve(n + 5);
    for (int i = 0; i < n; ++i) {
        cin >> l >> r;
        nums.emplace_back(l, r);
    }
    sort(nums.begin(), nums.end(), [](const node &n1, const node &n2) {
        return n1.l < n2.l;
    });

    int res = INT_MIN;
    for (int i = 0; i < n; ++i) {
        f[i] = 1;
        for (int j = 0; j < i; ++j) {
            if (nums[i].r > nums[j].r) {
                f[i] = max(f[i], f[j] + 1);
            }
        }
        res = max(res, f[i]);
    }
    cout << res << endl;
    return 0;
}