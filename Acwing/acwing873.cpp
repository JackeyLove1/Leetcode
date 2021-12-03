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
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

constexpr int MOD = 1e9 + 7;

inline int phi(int x){
    int res = x;
    for(int i = 2; i <= x / i; ++i){
        if(x % i == 0){
            res = res / i * (i-1);
            while (x % i == 0) x /= i;
        }
    }
    if(x > 1) res = res / x * (x-1);
    return res;
}


int main(){
    fhj();
    int n;
    cin >> n;
    while (n--){
        int x;
        cin >> x;
        cout << phi(x)<< endl;
    }
    return 0;
}