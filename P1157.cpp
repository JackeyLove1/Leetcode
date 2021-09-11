#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
#include <unordered_map>
#include <bitset>
#include <cstring>
#include <queue>

using namespace std;

constexpr int N = 1e3 + 100;
int n, m;

inline int count(int x) {
    int cnt = 0;
    while (x) {
        cnt += x & 1;
        x >>= 1;
    }
    return cnt;
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < (1 << n); ++i) {
        if (count(i) == m) {
            for (int j = 0; j < n; ++j) {
                if (i & (1 << j)) {
                    cout << j + 1 << "  ";
                }
            }
            cout << endl;
        }
    }
}