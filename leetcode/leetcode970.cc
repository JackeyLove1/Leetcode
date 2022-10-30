#pragma GCC optimize(2)

#include <bits/stdc++.h>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

template<typename T>
inline T read() {
    T ans = 0;
    char c = getchar();
    while (!isdigit(c)) c = getchar();
    while (isdigit(c)) ans = ans * 10 + c - '0', c = getchar();
    return ans;
}

using ll = long long;
#define rint read<int>()
#define rll read<ll>()

constexpr int N = 1e6 + 100;

class Solution1 {
public:
    int sumSubarrayMins(vector<int> &arr) {
        ll res = 0;
        const int mod = 1e9 + 7, N = arr.size();
        int f[N + 1];
        memset(f, 0x3f, sizeof f);
        for (int i = 0; i < N; ++i) {
            f[i] = 1e9;
            for (int j = i; j < N; ++j) {
                f[j + 1] = std::min(f[j], arr[j]);
                res = (res + f[j + 1]) % mod;
            }
        }
        return res;
    }
};

class Solution {
public:
    int sumSubarrayMins(vector<int> &arr) {
        long res = 0;
        const int mod = 1e9 + 7, N = arr.size();
        for_each(arr.begin(), arr.end(), [](int &x) { x = -x; });
        map<int, int> mp;
        for (int i = 0; i < N; ++i) {
            auto iter = mp.upper_bound(arr[i]);
            if (iter == mp.end()) {
                res = (res + 1l * (-arr[i]) * (i + 1)) % mod;
            } else {
                int diff = i - iter->second;
                res = (res + 1l * (-arr[i]) * (diff)) % mod;
            }
            mp[arr[i]] = i;
        }
        return res;
    }
};

int main() {
    Solution s{};
    vector<int> nums1{3,1,2,4};
    cout << s.sumSubarrayMins(nums1) << " res: 17" << endl;
    return 0;
}