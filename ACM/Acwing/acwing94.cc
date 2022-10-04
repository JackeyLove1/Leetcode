#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <set>
#include <cmath>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <functional>
#include <tuple>
#include <array>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

using ll = long long;
using ull = unsigned long long;
using PII = pair<int, int>;

constexpr int N = 1e5 + 100;
int n;

int main() {
    cin >> n;
    vector<int> vec(n, 0);
    std::iota(vec.begin(), vec.end(), 1);
    do{
        for_each(vec.begin(), vec.end(), [&](int num){cout << num << " "; });
        cout << endl;
    } while (next_permutation(vec.begin(), vec.end()));
    return 0;
}