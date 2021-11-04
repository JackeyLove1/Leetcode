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
    int n, k = 1;
    cin >> n;
    while (n > k) {
        n = n - k;
        k++;
    }
    if (k % 2 == 0) cout << n << "/" << (k + 1 - n);
    else cout << k + 1 - n << "/" << n;
    return 0;
}