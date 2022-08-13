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
constexpr int N = 1e3 + 100, INF = 0x3f3f3f3f;
int n, a, b, c, d;
vector<ll> d1, d2, nums;
int main() {
    fhj();
    cin >> n >> a >> b >> c >> d;
    d1.reserve(n), d2.reserve(n), nums.reserve(n);
    int x, y;
    auto dis1 = [&](int x, int y){
        return 1l * std::pow((x-a),2) + 1l * std::pow((y-b), 2);
    };
    auto dis2 = [&](int x, int y){
        return (ll)std::pow((x-c),2) + (ll)std::pow((y-d), 2);
    };
    for(int i = 0; i < n; ++i){
        cin >>x >>y;
        d1.emplace_back(dis1(x, y));
        d2.emplace_back(dis2(x, y));
        nums.emplace_back(i);
    }
    sort(nums.begin(), nums.end(), [](int x, int y){
        return d1[x] > d1[y];
    });
    ll res = d1[nums.front()];
    ll d2_num = 0;
    for(int i = 1; i < n; ++i){
        int j = nums[i-1];
        res = min(res, d1[i] + max((ll)d2[j], d2_num));
    }
    cout << min(res, max(d2_num, d2[nums.back()])) << endl;
    return 0;
}
