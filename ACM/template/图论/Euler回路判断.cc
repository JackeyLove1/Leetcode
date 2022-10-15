// 使用并查集判断连通性
// 使用度数判断是否是欧拉回路

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <cmath>
#include <stack>
#include <map>
#include <set>
using namespace std;
#define ms(x, n) memset(x,n,sizeof(x));
typedef  long long LL;
const int inf = 1<<30;
const LL maxn = 1e5+10;

int N, T, in[maxn], out[maxn];        //度表
bool vis[30];
char s[maxn];
int par[30], rak[30];
void init(int n) {
    for(int i = 0; i <= n; i++)
        par[i] = i, rak[i] = 0;
}
int findr(int x) {
    if(par[x] == x)
        return x;
    else
        return par[x] = findr(par[x]);
}
bool isSame(int x, int y) {
    return findr(x) == findr(y);
}
void unite(int x, int y) {
    x = findr(x);
    y = findr(y);
    if(x == y)
        return;
    if(rak[x] < rak[y])
        par[x] = y;
    else {
        par[y] = x;
        if(rak[x] == rak[y])
            rak[x]++; //如果rank相同则++
    }
}

bool judge(){
    int cnt1 = 0, cnt2 = 0;
    for(int i = 0; i < 26; i++){
        if(vis[i]){
            if(in[i]==out[i]) continue;
            else if(in[i]==out[i]+1){
                ++cnt1;
                if(cnt1>1) return false;
            }
            else if(in[i]==out[i]-1){
                ++cnt2;
                if(cnt2>1) return false;
            }
            else return false;
        }
    }
    if(cnt1+cnt2==1) return false;   //不要忘了这种情况
    return true;
}

int main()
{
    scanf("%d",&T);
    while(T--){
        ms(vis, 0); ms(in, 0); ms(out, 0);
        init(26);
        scanf("%d",&N);
        for(int i = 1; i <= N; i++){
            scanf("%s", s);
            int u = s[0]-'a', v = s[strlen(s)-1]-'a';
            ++in[u], ++out[v];  //每个单词都要经一次
            vis[u] = vis[v] = true;
            unite(u, v);
        }

        bool flag = false;
        int cnt = 0;
        for(int i = 0; i < 26; i++)
            if(vis[i] && findr(i)==i)
                ++cnt;
        if(cnt==1) flag = judge();
        if(flag)
            cout << "Ordering is possible." << endl;
        else
            cout << "The door cannot be opened." << endl;
    }

	return 0;
}


