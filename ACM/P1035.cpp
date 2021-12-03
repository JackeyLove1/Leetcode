#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <unordered_map>
#include <map>
#include <bitset>
#include <queue>
#include <deque>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

constexpr int N = 10;
int w[N];

int main() {
    int k;
    cin >> k;
    int res = 0;
    double sum = 0;
    while (sum <= k){
        ++res;
        sum += 1.0/res;
    }
    cout << res << endl;
    return 0;
}