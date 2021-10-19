// Author: Jacky
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <functional>
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
#include <numeric>


using namespace std;
using PII = pair<int, int>;
using ll = long long;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}


int main() {
    fhj();
    int t;
    cin >> t;
    int a, b;
    while (t--) {
        cin >> a >> b;
        while (b > 1) {
            if (b % a != 0) break;
            b /= a;
        }
        if (b == 1) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}