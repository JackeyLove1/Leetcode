#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <set>
#include <cmath>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <functional>
#include <tuple>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using PII = pair<int, int>;


static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 1e5 + 100, M = 65, INF = 0x3f3f3f3f, MOD = 1e4;

int a[20];
ll dp[20][20];

ll dfs(int pos, bool state, bool limit) {
    if (pos == -1) return 1;
    auto &ret = dp[pos][state];
    if (!limit && ret != -1) return ret;
    int up = limit ? a[pos] : 9;
    ll ans = 0;
    for (int i = 0; i <= up; i++) {
        if (i == 4 || (state && i == 2)) {
            continue;
        }
        ans += dfs(pos - 1, i == 6, limit && i == a[pos]);
    }

    if (!limit) ret = ans;
    return ans;
}

ll solve(ll x) {
    int pos = 0;
    while (x) {
        a[pos++] = x % 10;
        x /= 10;
    }
    return dfs(pos - 1, false, true);
}

int main() {
    ll l, r;
    memset(dp, -1, sizeof dp);
    while (~scanf("%lld%lld", &l, &r) && (l || r)) {
        printf("%lld\n", solve(r) - solve(l - 1));
    }
}

//
ll a,b;
ll f[20][12][2][2];
// len pre lim zero 
ll s[20];

ll dfs(ll len,ll pre,bool lim,bool zero)
{
	ll &tmp=f[len][pre][lim][zero];
	if(~tmp) return tmp;
	if(!len) return tmp=1;
	tmp=0;
	ll maxx=lim?s[len]:9;//卡最高位
	ll minn=zero?1:0;//卡前导零
	for(ll i=minn;i<=maxx;i++)
	{
		if(abs(i-pre)<2) continue;
		tmp+=dfs(len-1,i,lim&&(i==maxx),0);
	}
	return tmp;
}