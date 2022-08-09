#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <cmath>
#include <unordered_map>
#include <unordered_set>


using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

using ull = unsigned long long;
using ll = long long;
using PII = pair<int, int>;
constexpr int N = 1e6 + 1000;
int n, k;
int a[N];

int main() {
    fhj();
    cin >> n >> k;
    int x;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    sort(a + 1, a + 1 + n);
    int res = 0;
    for (int i = 1; i <= n; ++i) {
        int target = a[i] + k;
        int l = i + 1, r = n;
        while (l < r) {
            // find the first idx making a[idx] <= target
            int mid = l + r + 1 >> 1;
            if (a[mid] > target) r = mid - 1;
            else l = mid;
        }
        if (a[l] > a[i] && a[l] <= target) ++res;
    }
    cout << n - res << endl;
    return 0;
}