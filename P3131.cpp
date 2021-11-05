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


constexpr int N = 5e4 + 100;
int n, m;
int w[N], s[N];

int main() {
    fhj();
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> w[i];
        s[i] = s[i - 1] + w[i];
    }
    for (int len = n; len >= 1; --len) {
        for (int i = 1; i + len - 1 <= n; ++i) {
            int j = i + len - 1;
            // cout <<"i: " << i <<" j: " << j <<" res: " << s[j] - s[i-1] << endl;
            if ((s[j] - s[i - 1]) % 7 == 0) {
                cout << len << endl;
                return 0;
            }
        }
    }
    cout << 0 << endl;
    return 0;
}