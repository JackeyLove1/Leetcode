// Author: Jacky
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <functional>
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
#include <numeric>


using namespace std;
using PII = pair<int, int>;
using ll = long long;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

inline int count(int x) {
    return __builtin_popcount(x);
}

constexpr int N = 5500;

# include <cstdio>
# include <algorithm>

# define F(i, a, b) for (int i = a; i < b; i++)
using namespace std;

struct MG {
    int l, w;

    bool operator<(const MG &x) const {    //重定向小于号用于排序
        return l == x.l ? w > x.w : l > x.l;
    }

    friend ostream &operator<<(ostream &os, const MG &m) {
        os << m.l << " " << m.w << endl;
        return os;
    }
} m[5050];

/*								//也可以不重定向小于号，定义比较函数
bool cmp(MG x, MG y){
	if (x.l != y.l) return x.l > y.l;
    else return x.w > y.w;
}
*/
int f[5050];        //dp
int main() {
    int n, ans = 0;
    scanf("%d", &n);
    F(i, 0, n) scanf("%d%d", &m[i].l, &m[i].w);
    sort(m, m + n);                        //根据先前重定向的小于号排序
    //sort(m, m + n, cmp)     //如果先前定义比较函数要这样写
    for(int i = 0; i < n; ++i){
        cout << m[i];
    }
    F(i, 0, n) {
        for (int j = i - 1; j >= 0; j--) {
            if (m[i].w > m[j].w) f[i] = max(f[i], f[j] + 1);
        }
        ans = max(ans, f[i]);        //更新ans的值
    }
    for (int i = 0; i < n; ++i) {
        cout << f[i] << "  ";
    }
    cout << endl;
    printf("%d\n", ans + 1); //加上最大上升子序列的最后一个元素
    return 0;
}