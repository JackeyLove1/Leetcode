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

constexpr int N = 10;
int n, m;

int main() {
    fhj();
    cin >> n >> m;
    int cnt = 0;
    for (int i = 1; i <= n; ++i) {
        int b = i;
        while (b) {
            if (b % 10 == m) ++cnt;
            b /= 10;
        }
    }
    cout << cnt << endl;
    return 0;
}