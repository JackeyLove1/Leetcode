#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <map>
#include <set>
#include <bitset>
#include <cstring>
#include <queue>
#include <tuple>

using namespace std;

int n;

inline bool solve(int a, int b, int c) {
    return (a + b > c) && (a + c > b) && (b + c > a);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    using TIII = tuple<int, int, int>;
    set<TIII> s;
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }
    sort(nums.begin(), nums.end());
    int res = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            for(int k = j + 1; k < n; ++k){
                if(solve(nums[i], nums[j], nums[k])){
                    TIII t = {nums[i], nums[j], nums[k]};
                    if(s.count(t)) continue;
                    ++res;
                    s.insert(t);
                }
            }
        }
    }
    cout << res << endl;
}