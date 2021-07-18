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
int a[N];
using LL = long long;

int main() {
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a, a + n);
    int mid = a[n / 2];
    LL res = 0;
    for (int i = 0; i < n; i++) {
        res += abs(a[i] - mid);
    }
    cout << res << endl;
    return 0;
}