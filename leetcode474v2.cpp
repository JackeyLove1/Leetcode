#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>

using namespace std;

template<typename T>
inline void print1(vector<T> &nums) {
    for (auto &num : nums) cout << num << " ";
    cout << endl;
}

class Solution {
    static constexpr int N = 700, M = 120;
    int f[N][M][M];
public:
    using PII = pair<int, int>;

    inline PII count(string &str) {
        int m = 0, n = 0;
        for (auto &ch : str) {
            if (ch == '0') m++;
            else n++;
        }
        return {m, n};
    }

    int findMaxForm(vector<string> &strs, int m, int n) {
        int sz = strs.size();
        vector<PII> bags;
        bags.reserve(sz);
        for (auto &str : strs) {
            bags.push_back(count(str));
        }

        for (int k = 1; k <= sz; k++) {
            auto&&[zero, one] = bags[k - 1];
            for (int i = 0; i <= m; i++) {
                for (int j = 0; j <= n; j++) {
                    int a = f[k - 1][i][j];
                    int b = (i >= zero && j >= one) ? f[k - 1][i - zero][j - one] + 1 : 0;
                    f[k][i][j] = max(a, b);
                }
            }
        }
        return f[sz][m][n];
    }
};

int main() {

}