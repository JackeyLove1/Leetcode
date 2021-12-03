#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <climits>
#include <unordered_map>

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

using ll = long long;

//inline int cnt(int x) {
//    return __builtin_popcount(x);
//}

constexpr int N = 1e5 + 10;
int k[10001], ans;
int cnt[401][10001];
struct p {
    int h, a, c;
} b[401];

bool cmp(p a, p b) {
    return a.a < b.a;
}

int n;

int main() {
    k[0] = 1;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> b[i].h >> b[i].a >> b[i].c;//读入
    sort(b + 1, b + 1 + n, cmp);//排序
    for (int i = 1; i <= n; i++) {
        for (int j = b[i].h; j <= b[i].a; j++) {
            if (k[j] == 1)
                continue;
            if (k[j - b[i].h] == 1 && cnt[i][j - b[i].h] < b[i].c) {
                k[j] = k[j - b[i].h];
                cnt[i][j] = cnt[i][j - b[i].h] + 1;
                ans = max(j, ans);//
            }
            /*这两个if语句用到了一个贪心的思路
            对于高度j，可能有多种的摆搭方式，
            按照贪心的思路，我们应让第i块石头尽量少
            第1~i-1块石头尽量多
            （因为1~i-1的状态是已经确定的了，
            所以为了目前能垒的更高，所以要尽量少用当前的石头）
            因此，如果k[j]已经有值了，说明能用更少的第i块石头
            垒出高度为j的太空电梯，所以不用变动cnt的值，直接continue;*/
        }
    }
    cout << ans << endl;
    return 0;
}