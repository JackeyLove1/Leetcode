// 最长连续不重复子序列

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <unordered_map>

using namespace std;

const int N = 1e5 + 100;

int q[N];

int main() {
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> q[i];
    }
    unordered_map<int, int> m;
    int res = 1;
    // i不断向右扩展，再调整j的位置（也是向右扩展）
    for (int i = 0, j = 0; i < n; i++) {
        m[q[i]]++;
        while (j < i && m[q[i]] > 1) m[q[j++]]--;
        res = max(res, i - j + 1);
    }
    cout << res << endl;
    return 0;
}