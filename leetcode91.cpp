#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <functional>
#include <queue>
#include <set>

using namespace std;

int numDecodings(string s) {
    if (s.empty()) return 0;
    int n = s.size();
    vector<int> f(n + 1);
    f[0] = 1;
    for (int i = 1; i <= n; i++) {
        if (s[i - 1] != '0') {
            f[i] += f[i - 1];
        }
        if (i > 1 && s[i - 2] != '0' && (10 * (s[i - 2] - '0') + s[i - 1] - '0') <= 26) {
            f[i] += f[i - 2];
        }
    }
    return f[n];
}