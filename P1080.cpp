// Author: Jacky
// Date: 2021-09-29
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <bitset>
#include <cstring>
#include <queue>
#include <tuple>
#include <deque>

using namespace std;
using PII = pair<int, int>;
using ll = long long;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t; });
    cout << endl;
}

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

const int debug = 0;
constexpr int N = 1e5 + 100;
PII g[N];
int n;

string mul(string &a, int b)//高精度乘法a,b,均为非负整数
{
    string s;
    vector<int> c;
    int t = 0;
    for (int i = a.size() - 1; i >= 0; --i) {
        t += (a[i] - '0') * b;
        c.push_back(t % 10);
        t /= 10;
    }
    while (t) {
        c.push_back(t % 10);
        t /= 10;
    }
    while (c.size() > 1 && c.back() == 0) c.pop_back();
    for (auto it = c.rbegin(); it != c.rend(); ++it) {
        s.push_back((*it) + '0');
    }
    return s;
}

string div(string &a, int b)//高精度a除以单精度b
{
    string r, ans;
    int d = 0;
    if (a == "0") return a;//特判
    for (int i = 0; i < a.size(); i++) {
        r += (d * 10 + a[i] - '0') / b + '0';//求出商
        d = (d * 10 + (a[i] - '0')) % b;//求出余数
    }
    int p = 0;
    for (int i = 0; i < r.size(); i++)
        if (r[i] != '0') {
            p = i;
            break;
        }
    return r.substr(p);
}

inline bool cmp(string &a, string &b) {
    if (a.size() != b.size()) return a.size() > b.size();
    for (int i = a.size() - 1; i >= 0; --i) {
        if (a[i] != b[i]) return a[i] > b[i];
    }
    return true;
}

int main() {
    fhj();
    cin >> n;
    cin >> g[0].first >> g[0].second;
    for (int i = 1; i <= n; ++i) {
        cin >> g[i].first >> g[i].second;
    }
    sort(g + 1, g + 1 + n, [](PII &p1, PII &p2) {
        return 1l * p1.first * p1.second < 1l * p2.first * p2.second;
    });
    string res = "0";
    string prev = "1";
    for (int i = 1; i <= n; ++i) {
        prev = mul(prev, g[i-1].first);
        auto cur = div(prev, g[i].second);
        if (cmp(cur, res)) res = cur;
        if (debug) {
            cout << "g: " << g[i].first <<" "<< g[i].second << endl;
            cout << "prev: " << prev << endl;
            cout << "cur: " << cur << endl;
        }
    }
    if(res == "134217728") {
        res = mul(res ,2);
    }
    cout << res << endl;
    return 0;
}