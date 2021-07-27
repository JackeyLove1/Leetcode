#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <tuple>


using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for (auto &num : nums) cout << num << " ";
    cout << endl;
}

template<typename T>
inline void print(vector<vector<T>> &nums) {
    for (auto &num : nums) {
        for (auto &n : num) {
            cout << n << " ";
        }
        cout << endl;
    }
    cout << "ending ... " << endl;
}

const int N = 100010;
using ll = long long;
int n;
int a[N], b[N];

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) b[i] = a[i] - a[i - 1];

    ll p = 0, q = 0;
    for (int i = 2; i <= n; i++) {
        if (b[i] > 0) p += b[i]; // 需要的positive操作
        else q -= b[i]; // negtive操作
    }
    cout << max(p, q) << endl;
    cout << abs(p - q) + 1 << endl;
    return 0;
}