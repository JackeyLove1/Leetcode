#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <cmath>
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
constexpr int N = 1e6 + 1000;
int n, k;
vector<int> v;

int main() {
    fhj();
    cin >> n >> k;
    v.reserve(n);
    int x;
    for (int i = 0; i < n; ++i) {
        cin >> x;
        v.push_back(x);
    }
    sort(v.begin(), v.end());
    for_each(v.begin(), v.end(), [](int x){cout << x << " ";});
    cout << endl;
    int res = 0;
    auto p = v.begin();
    while (p != v.end()) {
        int target = *p + k;
        auto it = lower_bound(v.begin(), v.end(), target);
        if (it == v.end()){
            break;
        }else{
            auto flag = true;
            if (*it - *p > k) flag = false;
            if (flag){
                ++res;
                // cout <<"*p: "<< *p <<" *it " << *it ;
                // cout << " erase" << endl;
            }
            ++p;
        }
    }
    cout << n - res << endl;
    return 0;
}