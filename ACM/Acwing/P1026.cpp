#include <unordered_map>
#include <unordered_set>
#include <map>
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>
#include <queue>
#include <set>
#include <tuple>
#include <list>
#include <atomic>
#include <thread>

#include <cstring>
#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

template<typename T>
static inline void print(const vector<T> &nums) {
    if (nums.empty()) {
        cout << " empty !" << endl;
        return;
    }
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

inline int count(int state) {
    return __builtin_popcount(state);
}

constexpr int N = 210;
int f[N][50], sum[N][N];
int p, m, s;
string words;
string ch;
unordered_map<string, int> um;

int main() {
    fhj();
    words = " ";
    cin >> p >> m;
    for (int i = 0; i < p; ++i) {
        cin >> ch;
        words += ch;
    }
    for (int i = 0; i < s; ++i) {
        cin >> ch;
        um[ch]++;
    }
    int n = words.size() - 1;
    for (int i = n; i >= 1; --i) {
        for (int j = i; j >= 1; --j) {
            sum[j][i] = sum[j + 1][i];
            if (um.count(words.substr(j, i - j + 1)))
                sum[j][i]++;
        }
    }
    for(int i = 1; i <= m; ++i) f[i][i] = f[i-1][i-1] + sum[i][i];
    for(int i = 1; i <= n; ++i) f[i][1] = sum[1][i];
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= m && j <= i; ++j){
            for(int k = j; k < i; ++k){
                f[i][j] = max(f[i][j], f[k][j-1] + sum[k+1][i]);
            }
        }
    }
    cout << f[n][m] << endl;
    return 0;
}
