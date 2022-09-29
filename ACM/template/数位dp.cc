#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <functional>
#include <numeric>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

using ll = long long;
constexpr int N = 1e5 + 100;

const int state = 10;
int a[20];
ll dp[20][state];//不同题目状态不同
ll dfs(int pos/*state变量*/,bool lead/*前导零*/,bool limit/*数位上界变量*/)//不是每个题都要判断前导零
{
//递归边界，既然是按位枚举，最低位是0，那么pos==-1说明这个数我枚举完了
if(pos==-1) return 1;/*这里一般返回1，表示你枚举的这个数是合法的，那么这里就需要你在枚举时必须每一位都要满足题目条件，也就是说当前枚举到pos位，一定要保证前面已经枚举的数位是合法的。不过具体题目不同或者写法不同的话不一定要返回1 */
//第二个就是记忆化(在此前可能不同题目还能有一些剪枝)
if(!limit && !lead && dp[pos][state]!=-1) return dp[pos][state];
/*常规写法都是在没有限制的条件记忆化，这里与下面记录状态是对应，具体为什么是有条件的记忆化后面会讲*/
int up=limit?a[pos]:9;//根据limit判断枚举的上界up;这个的例子前面用213讲过了
ll ans=0;
//开始计数
for(int i=0;i<=up;i++)//枚举，然后把不同情况的个数加到ans就可以了
{
if() ...
else if()...
ans+=dfs(pos-1,/*状态转移*/,lead && i==0,limit && i==a[pos]) //最后两个变量传参都是这样写的
/*这里还算比较灵活，不过做几个题就觉得这里也是套路了
大概就是说，我当前数位枚举的数是i，然后根据题目的约束条件分类讨论
去计算不同情况下的个数，还有要根据state变量来保证i的合法性，比如题目
要求数位上不能有62连续出现,那么就是state就是要保存前一位pre,然后分类，
前一位如果是6那么这意味就不能是2，这里一定要保存枚举的这个数是合法*/
}
//计算完，记录状态
if(!limit && !lead) dp[pos][state]=ans;
/*这里对应上面的记忆化，在一定条件下时记录，保证一致性，当然如果约束条件不需要考虑lead，这里就是lead就完全不用考虑了*/
return ans;
}
ll solve(ll x)
{
    int pos=0;
    while(x)//把数位都分解出来
    {
        a[pos++]=x%10;//个人老是喜欢编号为[0,pos),看不惯的就按自己习惯来，反正注意数位边界就行
        x/=10;
    }
    return dfs(pos-1/*从最高位开始枚举*/,/*一系列状态 */,true,true);//刚开始最高位都是有限制并且有前导零的，显然比最高位还要高的一位视为0嘛
}
int main()
{
    ll le,ri;
    while(~scanf("%lld%lld",&le,&ri))
    {
        //初始化dp数组为-1,这里还有更加优美的优化,后面讲
        printf("%lld\n",solve(ri)-solve(le-1));
    }
}

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

/*
#include <iostream>

using namespace std;

const int N = 10;

int f[N][N];//f[i][j] 表示 我们填到第i位，当第i位填j的时候有多少种合适的车牌

void init()//数位DP日常初始化
{
    for(int i = 0;i <= 9;i ++) f[1][i] = 1; //日常水掉第一位
    f[1][4] = 0;                            //显然
    for(int i = 2;i <= N;i ++)              //从第2位开始填
        for(int j = 0;j <= 9;j ++)      //j表示第i位我想要拿着j去看看能不能填
            for(int k = 0;k <= 9;k ++)//k表示第i - 1位我填的什么，i - 1 位是我们之前填好的，所以可以拿来用
            {
                if(k == 4 || j == 4) continue;
                if(j == 6 && k == 2) continue;//如果第i位是6，i - 1位是2肯定是不行的
                f[i][j] += f[i - 1][k];//日常状态转移
            }
}

int dp(int x)
{
    if(!x) return 1;                        //日常边界判断，有的数位DP题里必须有，这道题需不需要你交一下试试就知道了

    int a[12] = {0};                        //我要用a数组把这个数的每一位都取出来
    int l = 0;
    int ans = 0;
    int last = 0;                           //last用来看上一位是不是6，如果是6 那么这一位我就不能填2了
    while(x)
    {
        a[++ l] = x % 10;
        x /= 10;
    }

    for(int i = l;i >= 1;i --)
    {
        for(int j = 0;j < a[i];j ++)    //因为是车牌，所以第一位可以是0，故从0循环
        {
            if(j == 4) continue;
            if(last == 6 && j == 2) continue;
            ans += f[i][j];
        }
        if(a[i] == 4) break;
        if(a[i] == 2 && last == 6) break;

        last = a[i];
        if(i == 1) ans ++;              //本来没加这句话，但是写完发现答案少一，于是加上，表示所有的都填完了，传进来的这个x也能填
    }

    return ans;
}

int main()
{
    init();
    int l,r;
    while(cin >> l >> r,l && r)
    {
        cout << dp(r) - dp(l - 1) << endl;
    }
    return 0;
}
*/

ll dp[12][13][10][2];

ll dfs(int pos, int mod, int pre, int have13, bool limit) {
    if (pos == 0) return have13 && mod == 0;
    auto &ret = dp[pos][mod][pre][have13];
    if (!limit && ret != -1) return ret;
    int up = limit ? a[pos] : 9;
    ll ans = 0;
    for (int i = 0; i <= up; i++) {
        if (pre == 1 && i == 3) ans += dfs(pos - 1, (mod * 10 + i) % 13, i, 1, limit && i == up);
        else ans += dfs(pos - 1, (mod * 10 + i) % 13, i, have13, limit && i == up);
    }
    if (!limit) ret = ans;
    return ans;
}

ll solve(ll x) {
    int pos = 0;
    while (x) {
        a[++pos] = x % 10;
        x /= 10;
    }
    return dfs(pos, 0, 0, 0, 1);
}

// 考虑前导零版本
LL dfs(int pos, int pre, int len, bool leadingzero, bool limit){//pos--当前位，pre--更高一位的数是奇还是偶，len--连续长度，leadingzero--是否有前导零，limit--当前位的数字是否有限制
    if(!pos) return (pre & 1) != (len & 1);
    if(!limit && dp[pos][pre][len] != -1) return dp[pos][pre][len];
    LL ans = 0;
    int up = limit ? digit[pos] : 9;
    for(int i = 0; i <= up; ++i){
        if(leadingzero){
            if(i == 0){
                ans += dfs(pos - 1, 0, 0, true, limit && i == up);
            }
            else{
                ans += dfs(pos - 1, i & 1, 1, false, limit && i == up);
            }
        }
        else{
            if(i & 1){
                if(pre & 1){
                    ans += dfs(pos - 1, i & 1, len + 1, false, limit && i == up);
                }
                else{
                    if(len & 1){//若当前位是奇数，前一位是偶数，且已经有奇数长度的偶数，则可以继续延伸
                        ans += dfs(pos - 1, i & 1, 1, false, limit && i == up);
                    }
                }
            }
            else{
                if(pre & 1){
                    if(!(len & 1)){
                        ans += dfs(pos - 1, i & 1, 1, false, limit && i == up);
                    }
                }
                else{
                    ans += dfs(pos - 1, i & 1, len + 1, false, limit && i == up);
                }
            }
        }
    }
    if(!limit) dp[pos][pre][len] = ans;
    return ans;
}
LL solve(LL x){
    int cnt = 0;
    while(x){
        digit[++cnt] = x % 10;
        x /= 10;
    }
    return dfs(cnt, 0, 0, true, true);
}
int main(){
    int T;
    scanf("%d", &T);
    int kase = 0;
    memset(dp, -1, sizeof dp);
    while(T--){
        LL L, R;
        scanf("%lld%lld", &L, &R);
        printf("Case #%d: %lld\n", ++kase, solve(R) - solve(L - 1));
    }
    return 0;
}
