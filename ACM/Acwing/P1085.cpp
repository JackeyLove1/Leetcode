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
    fhj();
    for (int i = 1; i <= 7; ++i) {
        int a, b;
        cin >> a >> b;
        w[i] = a + b;
    }
    int res = 0, h = 8;
    for (int i = 1; i <= 7; ++i) {
        if (w[i] > h) {
            res = i;
            break;
        }
    }
    cout << res << endl;
    return 0;
}