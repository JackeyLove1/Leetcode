#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <bitset>
#include <cstring>
#include <string>
#include <numeric>

using namespace std;

template<typename T>
inline void print(vector<vector<T>> &nums) {
    for (auto &num : nums) {
        for_each(num.begin(), num.end(), [](const T &t) { cout << t << " "; });
        cout << endl;
    }
}

template<typename T>
inline void print(vector<T> &num) {
    for_each(num.begin(), num.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

class Solution {
public:
    int maxCompatibilitySum(vector<vector<int>> &students, vector<vector<int>> &mentors) {
        int m = students.size(), n = students[0].size();
        vector<vector<int>> record(m, vector<int>(m, 0));

        auto check = [&](vector<int> &v1, vector<int> &v2) -> int {
            int res = 0;
            for (int i = 0; i < n; i++) {
                if (v1[i] == v2[i]) ++res;
            }
            return res;
        };

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                record[i][j] = check(students[i], mentors[j]);
            }
        }
        vector<int> per;
        for (int i = 0; i < m; i++) {
            per.push_back(i);
        }
        // print(per);
        int res = 0;
        do {
            int tmp = 0;
            for (int i = 0; i < m; i++) {
                tmp += record[i][per[i]];
            }
            res = max(res, tmp);
        } while (next_permutation(per.begin(), per.end()));
        return res;
    }
};

class Solution1 {
public:
    int maxCompatibilitySum(vector<vector<int>>& students, vector<vector<int>>& mentors) {
        int m = students.size();
        int n = students[0].size();
        vector<vector<int>> g(m, vector<int>(m));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < m; ++j) {
                for (int k = 0; k < n; ++k) {
                    g[i][j] += (students[i][k] == mentors[j][k]);
                }
            }
        }

        vector<int> p(m);
        iota(p.begin(), p.end(), 0);
        print(p);
        int ans = 0;
        do {
            int cur = 0;
            for (int i = 0; i < m; ++i) {
                cur += g[i][p[i]];
            }
            ans = max(ans, cur);
        } while (next_permutation(p.begin(), p.end()));
        return ans;
    }
};

class Solution2 {
public:
    int maxCompatibilitySum(vector<vector<int>> &students, vector<vector<int>> &mentors) {
        int m = students.size();
        int n = students[0].size();
        vector<vector<int>> g(m, vector<int>(m));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < m; ++j) {
                for (int k = 0; k < n; ++k) {
                    g[i][j] += (students[i][k] == mentors[j][k]);
                }
            }
        }

        vector<int> f(1 << m);
        for (int i = 0; i < 1 << m; i++) {
            int c = __builtin_popcount(i);
            for (int j = 0; j < m; j++) {
                if (i & (1 << j)) {
                    f[i] = max(f[i], f[i ^ (1 << j)] + g[c - 1][j]);
                }
            }
        }
        return f[(1 << m) - 1];
    }
};


int main(){
    auto s = Solution();
    vector<vector<int>> stu = {{0,1,0,1,1,1},{1,0,0,1,0,1},{1,0,1,1,0,0}};
    vector<vector<int>> tea = {{1,0,0,0,0,1},{0,1,0,0,1,1},{0,1,0,0,1,1}};
    cout << s.maxCompatibilitySum(stu, tea) <<" res:10 ";
    auto s1 = Solution1();
    cout << s1.maxCompatibilitySum(stu, tea) <<" res:10 ";
    return 0;
}