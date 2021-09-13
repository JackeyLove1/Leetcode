#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <bitset>
#include <cstring>
#include <queue>
#include <random>

using namespace std;

void print(vector<int> &nums) {
    for (auto &num : nums) {
        cout << num << " ";
    }
    cout << endl;
}


class Solutionv1 {
public:
    string reversePrefix(string word, char ch) {
        for (int i = 0; i < word.size(); ++i) {
            if (word[i] == ch) {
                reverse(word.begin(), word.begin() + i + 1);
                break;
            }
        }
        return word;
    }
};

class Solutionv2 {
public:
    long long interchangeableRectangles(vector<vector<int>> &rectangles) {
        using ll = long long;
        ll res = 0;
        auto f = [](int n) -> ll {
            return 1l * n * (n - 1) / 2;
        };
        unordered_map<double, vector<int>> m;
        for (int i = 0; i < rectangles.size(); ++i) {
            auto rec = rectangles[i];
            m[(double(rec[0]) / rec[1])].push_back(i);
        }
        for (auto&[_, v] : m) {
            res += f(v.size());
        }
        return res;
    }
};

class Solutionv3 {
public:
    int n;
    string a, b, _s;
    int res;

    bool check(string &str) {
        int k = str.size() - 1;
        for (int i = 0, j = k; i < j; ++i, --j) {
            if (str[i] != str[j]) return false;
        }
        return true;
    }

    void dfs(int k) {
        if (k == n) {
            if (check(a) && check(b)) {
                res = max(res, int(a.size() * b.size()));
            }
            return ;
        }
        a.push_back(_s[k]);
        dfs(k + 1);
        a.pop_back();

        b.push_back(_s[k]);
        dfs(k + 1);
        b.pop_back();

        dfs(k + 1);
    }

    int maxProduct(string s) {
        n = s.size(), res = 0, _s = s, a = "", b = "";
        dfs(0);
        return res;
    }
};

class Solutionv4 {
private:
    using PII = pair<int, int>;

    static constexpr int N = 1e6 + 100, M = 1e5 + 10;

    int e[N], ne[N], h[N], idx;

    inline void init() {
        idx = 0;
        memset(h, -1, sizeof h);
    }

    inline void add(int a, int b) {
        e[idx] = b, ne[idx] = h[a], h[a] = idx++;
    }

public:

    vector<int> smallestMissingValueSubtree(vector<int> &parents, vector<int> &nums) {
        init();
        int n = parents.size();
        for (int i = 1; i < n; ++i) {
            add(parents[i], i);
        }
        vector<int> res;
        bitset<M> f[n + 1];
        function<void(int)> dfs = [&](int idx) -> void {
            if (f[idx].to_ullong()) return;
            f[idx][nums[idx]] = true;
            for (int i = h[idx]; i != -1; i = ne[i]) {
                int j = e[i];
                dfs(j);
                f[idx] |= f[j];
            }
            // cout << f[idx] << endl;
        };
        dfs(0);
        for (int i = 0; i < n; ++i) {
            for (int j = 1; j <= n + 1; ++j) {
                if (f[i][j]) continue;
                else {
                    res.push_back(j);
                    break;
                }
            }
        }
        return res;
    }
};

class Solutionv4_2 {
private:
    static constexpr int N = 1e6 + 100, M = 1e5 + 10;

    int e[N], ne[N], h[N], idx;

    inline void init() {
        idx = 0;
        memset(h, -1, sizeof h);
    }

    inline void add(int a, int b) {
        e[idx] = b, ne[idx] = h[a], h[a] = idx++;
    }

public:
    void dfs(int p, vector<bitset<M>> &f, vector<int> &nums) {
        if (f[p].to_ullong()) return;
        f[p][nums[p]] = true;
        for (int i = h[p]; i != -1; i = ne[i]) {
            int j = e[i];
            dfs(j, f, nums);
            f[p] |= f[j];
        }
    }

    vector<int> smallestMissingValueSubtree(vector<int> &parents, vector<int> &nums) {
        init();
        int n = parents.size();
        for (int i = 1; i < n; ++i) {
            add(parents[i], i);
        }
        vector<int> res;
        vector<bitset<M>> f(n + 2);
        dfs(0, f, nums);
        for (int i = 0; i < n; ++i) {
            for (int j = 1; j <= n + 1; ++j) {
                if (f[i][j]) continue;
                else {
                    res.push_back(j);
                    break;
                }
            }
        }
        return res;
    }
};

