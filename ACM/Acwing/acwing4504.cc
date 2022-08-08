#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <queue>
#include <functional>
#include <numeric>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <unordered_map>
#include <unordered_set>


using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

using ull = unsigned long long;
using ll = long long;
using PII = pair<int, int>;
constexpr int N = 1e5 + 100;
string s;

int main() {
    fhj();
    cin >> s;
    vector<int> st;
    int cnt = 0;
    for (const auto &i: s) {
        if (st.empty()) st.push_back(i);
        else if (st.back() == i) {
            st.pop_back();
            ++cnt;
        } else {
            st.push_back(i);
        }
    }
    if (cnt & 1) cout << "Yes" << endl;
    else cout << "No" << endl;
    return 0;
}