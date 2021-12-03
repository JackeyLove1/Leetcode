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

void divide(int x){
    for(int i = 2 ;i <= x / i; ++i){
        if(x % i == 0){
            int s = 0;
            while (x % i == 0) x /= i, ++s;
            cout << i << " " << s << endl;
        }
    }
    if(x > 1) cout << x <<" " << 1 << endl;
    cout << endl;
}

int n;
int main(){
    fhj();
    cin >> n;
    while (n--){
        int x;
        cin >> x;
        divide(x);
    }
    return 0;
}