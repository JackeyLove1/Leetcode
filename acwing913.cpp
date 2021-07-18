#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <unordered_set>
#include <cstring>

using namespace std;

const int N = 100010;
int t[N];

using LL = long long;

int main() {
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> t[i];
    }
    sort(t, t + n);
    reverse(t, t + n);

    LL res = 0;
    for (int i = 0; i < n; i++) {
        res += t[i] * i;
    }
    cout << res << endl;
    return 0;
}