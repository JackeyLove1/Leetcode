#include <unordered_map>
#include <unordered_set>
#include <map>
#include <iostream>
#include <utility>
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

class Solution {
private:
    constexpr static int mod = 1e9 + 7;
    constexpr static int primes[25] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43,
                                       47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
    using ll = long long;

    int init(int n) {
        int cnt = 0;
        for (const int prime : primes) {
            if (n >= prime) ++cnt;
            else break;
        }
        return cnt;
    }

    ll A(int m) {
        ll res = 1;
        for (ll i = m; i >= 2; --i) {
            res = (res * i) % mod;
        }
        return res;
    }

public:
    int numPrimeArrangements(int n) {
        if(n <= 2) return 1;
        int x = init(n);
        int y = n - x;
        ll res = A(x) * A(y) % mod;
        // print(primes);
        return static_cast<int>(res);
    }
};

int main() {
    Solution s;
    cout << s.numPrimeArrangements(100) << ": 682289015" << endl;
}

