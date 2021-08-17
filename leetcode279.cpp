#include <iostream>
#include <algorithm>
#include <functional>
#include <cstring>
#include <vector>
#include <map>
#include <unordered_map>
#include <cmath>

using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

class Solution {
private:
    static constexpr int INF = 1e9;
public:
    int numSquares(int n) {
        int sq = int(sqrt(n));
        vector<int> v;
        vector<int> f(n + 1, INF);
        for (int i = 0; i <= sq; i++) {
            v.push_back(i * i);
            f[i * i] = 1;
        }
        for (int i = 0; i < v.size(); i++) {
            for (int j = 0; j <= n; j++) {
                if (j >= v[i]) {
                    f[j] = min(f[j - v[i]] + 1, f[j]);
                }
            }
        }
        return f[n];
    }
};

int main() {
    auto s = Solution();
    cout << s.numSquares(12) << " res: 3" << endl;
    cout << s.numSquares(13) << " res: 2" << endl;
    return 0;
}