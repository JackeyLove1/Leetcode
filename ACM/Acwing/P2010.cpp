#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <unordered_map>
#include <map>
#include <bitset>
#include <queue>
#include <deque>
#include <unordered_set>

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

constexpr int N = 110;

int i, j, n, m, a, b, c, sum, ans;
int s[13] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int main() {
    scanf("%d%d", &n, &m);
    for (i = 1; i <= 12; i++)//枚举月和日 
        for (j = 1; j <= s[i]; j++) {
            c = (j % 10) * 1000 +
                (j / 10) * 100 +
                (i % 10) * 10 +
                (i / 10);//算出前四位。
            sum = c * 10000 + i * 100 + j;//算出整个日期 
            if (sum < n || sum > m) continue;
            ans++;//统计 
        }
    printf("%d", ans);
    return 0;
}