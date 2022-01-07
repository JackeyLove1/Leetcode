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

inline int count(int state) {
    return __builtin_popcount(state);
}

constexpr int N = 5010;

struct node {
    int l, r;

    explicit node(int l_, int r_) : l(l_), r(r_) {}
};

int n;
vector<node> nums;
int l, r;
int f[N];

int main() {
    fhj();
    cin >> n;
    nums.reserve(N);
    for (int i = 0; i < n; ++i) {
        cin >> l >> r;
        nums.emplace_back(l, r);
    }
    sort(nums.begin(), nums.end(), [](const node &x, const node &y) {
        return x.l < y.l;
    });
    int res = 1;
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