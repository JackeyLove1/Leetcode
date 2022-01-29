#include <unordered_map>
#include <map>
#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <string>

// #pragma GCC optimize(2)

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

using PII = pair<int, int>;
int n, k;
int now[1110];
#define l first
#define r second

int main() {
    fhj();
    int T;
    cin >> T;
    vector<PII> nums;
    nums.reserve(110);
    while (T--) {
        cin >> n >> k;
        int st, ed;
        for (int i = 1; i <= n; ++i) {
            cin >> st >> ed;
            nums.emplace_back(st, ed);
        }
        sort(nums.begin(), nums.end(), [](const PII &p1, const PII &p2) {
            return p1.r == p2.r ? p1.l < p2.l : p1.r < p2.r;
        });
        int res = 0;
        for (int i = 0; i < n; i++) {
            int minn = 23333333;
            int nx = 0;
            for (int j = 0; j < k; j++)//同时数组now中能装K个人
            {//a[i].l-now[j]<minn指是在这个时间区间内
                if (nums[i].l > now[j] &&
                    nums[i].l - now[j] < minn)//每次比较都是跟上一个时间区间比较，每一个时间区间只能同时存在K个人，满了以后之后的都跟上一个时间区间比较
                {
                    nx = j;
                    minn = nums[i].l - now[j];//求得现在的时间区间
                }
            }
            if (nx != 0)//符合条件（上一个结束吃下一个人）就ans++
            {
                now[nx] = nums[i].r;
                ++res;
            }
        }
        cout << res << endl;
    }
    return 0;
}