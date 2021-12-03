#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <unordered_map>
#include <map>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

constexpr int N = 110, M = 1e5;

class Solution {
public:
    int countTriples(int n) {
        unordered_map<int, int> m;
        for (int i = 1; i <= n; ++i) {
            ++m[i * i];
        }
        int res = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (m.count(i * i + j * j)) ++res;
            }
        }
        return res;
    }
};