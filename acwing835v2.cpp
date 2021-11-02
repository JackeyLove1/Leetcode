#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <unordered_map>
#include <map>
#include <bitset>
#include <queue>
#include <deque>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

constexpr int N = 1e5 + 100;
int son[N][26], cnt[N], idx;

void insert(string &s) {
    int p = 0;
    for (int i = 0; i < s.size(); ++i) {
        int u = s[i] - 'a';
        if (!son[p][u]) son[p][u] = ++idx;
        p = son[p][u];
    }
    cnt[p]++;
}

int query(string &s) {
    int p = 0;
    for (char i : s) {
        int c = i - 'a';
        if (!son[p][c]) return 0;
        p = son[p][c];
    }
    return cnt[p];
}

int n;

int main() {
    fhj();
    cin >> n;
    char op;
    string str;
    while (n--) {
        cin >> op >> str;
        if (op == 'I') {
            insert(str);
        } else {
            cout << query(str) << endl;
        }
    }
    return 0;
}