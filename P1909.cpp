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

int i, j, k, n, m, w, ans;

int main() {
    scanf("%d", &n);
    for (i = 0; i < 3; i++) {
        scanf("%d%d", &j, &k);
        m = j;
        w = k;//输入并存下初始的价格与数量
        while (j < n) {
            j <<= 1;
            k <<= 1;
        }//价格与数量不断*2直到数量大于n
        while (j > n) {
            j -= m;
            k -= w;
        }//*2有可能导致买太多了，减去一些
        while (j < n) {
            j += m;
            k += w;
        }//减去之后又可能太少了，加上一些
        //其实就是大幅度地上调，然后做一些微调
        if (k < ans || ans == 0)ans = k;//判断是否是最小花费
    }
    printf("%d\n", ans);
    return 0;//输出并返回
}