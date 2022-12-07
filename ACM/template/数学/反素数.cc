#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

int primes[9] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
int maxd, number;
int n;

void dfs(int u, int last, int p, int s)
{
    if (s > maxd || s == maxd && p < number)
    {
        maxd = s;
        number = p;
    }

    if (u == 9) return;

    for (int i = 1; i <= last; i ++ )
    {
        if ((LL)p * primes[u] > n) break;
        p *= primes[u];
        dfs(u + 1, i, p, s * (i + 1));
    }
}

int main()
{
    cin >> n;

    dfs(0, 30, 1, 1); // 枚举到素数的下标，当前素数的次数，最大的反素数，约数的个数

    cout << number << endl;

    return 0;
}

/*
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int prime[10]={2,3,5,7,11,13,17,19,23};//前9个素数
ll ans;
int maxn=0;
ll n;
void dfs(int dep,int num,int limit,ll now)
//dep=当前枚举素数，num=当前数的因子数，limit=当前素数最多指数，now=当前数
{
    if(dep>8) return;//剪枝，更大的范围需要更大的限制
    if(num>maxn||(num==maxn&&now<ans)) maxn=num,ans=now;
    //若能更新答案，则更新
    for(int i=1;i<=limit;i++)//枚举当前素数的指数
    {
        if(prime[dep]*now>n) break;//如果再乘一次该素数超出边界则退出
        dfs(dep+1,num*(i+1),i,now*=prime[dep]);//枚举下一个素数
    }
}
int main()
{
    scanf("%lld",&n);//输出范围
    dfs(0,1,100,1);//limit随意输个较大数即可，最小是log2n
    printf("%lld\n",ans);
    return 0;
}
*/