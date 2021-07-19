#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <functional>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        int n, x;
        cin >> n;
        vector<int> v(n + 1);
        unordered_map<int, int> um;
        for (int i = 1; i <= n; i++) {
            cin >> x;
            v[i] = x, um[x]++;
        }
        int res = -1, num = 1e9;
        for (int i = 1; i <= n; i++) {
            if (um[v[i]] == 1 && v[i] < num) {
                res = i;
                num = v[i];
            }
        }
        cout << res << endl;
    }

    return 0;
}