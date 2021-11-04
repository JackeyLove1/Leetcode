#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <unordered_map>
#include <map>
#include <bitset>
#include <queue>
#include <deque>

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

constexpr int N = 20;
int n, m;
int w[N];

int main() {
    for (int i = 1; i <= 10; ++i) {
        cin >> w[i];
    }
    cin >> n;
    n += 30;
    int res = 0;
    for (int i = 1; i <= 10; ++i) {
        if (w[i] <= n) res++;
    }
    cout << res << endl;
    return 0;
}