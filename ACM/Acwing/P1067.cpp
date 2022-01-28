#include <unordered_map>
#include <map>
#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <string>

// #pragma GCC optimize(2)

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

inline string get(int num, int x) {
    if (num == 0) return "";
    if (num == 1 && x == 0) return "+1";
    string end;
    if (x > 1) end = "x^" + to_string(x);
    if (x == 1) end = "x";
    string begin;
    if (num == -1) begin = "-";
    else if (num != 1) {
        begin = "+" + to_string(num);
    }else if(num == 1){
        begin = "+";
    }
    // cout << "get: " << num << ' ' << x << " : " << begin + end << endl;
    return begin + end;
}


int main() {
    fhj();
    int n;
    cin >> n;
    vector<int> g;
    g.reserve(110);
    for (int i = 0; i <= n; ++i) {
        int num;
        cin >> num;
        g.push_back(num);
    }
    reverse(g.begin(), g.end());
    string res;
    for (int i = 0; i < g.size(); ++i) {
        string tmp = get(g[i], i);
        if (tmp.empty()) continue;
        res = tmp + res;
    }
    // res.pop_back();
    res.erase(res.begin());
    cout << res << endl;
    return 0;
}