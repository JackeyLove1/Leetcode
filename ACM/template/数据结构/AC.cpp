/*
// Luogu P3808 【模板】AC 自动机（简单版）
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

const int N=500010;
int n;char str[1000010];
int ch[N][26],cnt[N],idx;
int ne[N];

void insert(char *s){//建树
  int p=0;
  for(int i=0;s[i];i++){
    int j=s[i]-'a';
    if(!ch[p][j])ch[p][j]=++idx;
    p=ch[p][j];
  }
  cnt[p]++;
}
void build(){//建AC自动机
  queue<int> q;
  for(int i=0;i<26;i++)
    if(ch[0][i])q.push(ch[0][i]);
  while(q.size()){
    int u=q.front();q.pop();
    for(int i=0;i<26;i++){
      int v=ch[u][i];
      if(v)ne[v]=ch[ne[u]][i],q.push(v);
      else ch[u][i]=ch[ne[u]][i];
    }
  }
}
int query(char *s){
  int ans=0;
  for(int k=0,i=0;s[k];k++){
    i=ch[i][s[k]-'a'];
    for(int j=i;j&&~cnt[j];j=ne[j])
      ans+=cnt[j], cnt[j]=-1;
  }
  return ans;
}
int main(){
  cin>>n;
  for(int i=0;i<n; i++)
    cin>>str, insert(str);
  build();
  cin>>str;
  cout<<query(str)<<endl;
  return 0;
}
*/
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>

using namespace std;

const int N=10010,S=55,M=10000010;

int n;
int tr[N*S][26],cnt[N*S],idx;
char str[M];
int q[N*S],ne[N*S];
void insert()
{
    int p = 0;
    for(int i =0;str[i];i++)
    {
        int t = str[i]-'a';
        if(!tr[p][t]) tr[p][t] = ++idx;//如果儿子不存在 创建一个新的节点
        p = tr[p][t];// 沿字符串字母idx继续往下走
    }
    cnt[p] ++;
}
void build()
{
    int hh=0,tt=-1;
    for(int i=0;i<26;i++)//根节点以及第一层结点都是指向根节点，所以直接从第一层开始搜，也就是根的所有儿子开始搜
    {
        if(tr[0][i])
            q[++tt] = tr[0][i];
    }

    while(hh<=tt)
    {
        int t = q[hh++];//队列popleft
        for(int i=0;i<26;i++)
        {
            int p = tr[t][i];//p:自动机中某个第i层结点的idx -> KMP中的i 

            // 优化思路 在没有匹配时 把while循环多次跳 优化为 直接跳到ne指针最终跳到的位置
            // 假定在循环第i层时，前i-1层都求对了
            // 在第i层没找到字母i,那么去第i-1层父结点t的next指针的位置就是它最终应该跳到的位置
            if(!p) tr[t][i] = tr[ne[t]][i];//ne[t]:j  如果不存在儿子tr[t][i]的话
            // 如果存在儿子节点 则对儿子节点的next指针赋值为tr[ne[t]][i]
            else
            {
                ne[p] = tr[ne[t]][i];
                q[++tt] = p;
            }
        }
    }

}
int main()
{
    int T;
    scanf("%d", &T);
    while (T -- )
    {
        memset(tr, 0, sizeof tr);
        memset(cnt, 0, sizeof cnt);
        memset(ne, 0, sizeof ne);
        idx = 0;

        scanf("%d", &n);
        for (int i = 0; i < n; i ++ )
        {
            scanf("%s", str);
            insert();
        }

        build();

        scanf("%s", str);

        int res = 0;
        for (int i = 0, j = 0; str[i]; i ++ )
        {
            int t = str[i] - 'a';
            /*
            while(j && !tr[j][t]) j = ne[j];
            if(tr[j][t]) j=tr[j][t];
            int p = j;
             // she 和 he 的 e结点都有cnt[e]=1
                遍历到she的后缀he的时候 her的相同前缀he肯定是逐层遍历到了的 len(he)<len(she) 逐层遍历
                把所有ne 指针全部加一遍  比如当前p到了she的e  把cnt[p]+进res后 
                把p通过ne[p]跳到he的e 再加上此时指向he中e的p的cnt[p] 
            while(p)
            {
                res += cnt[p];
                cnt[p] = 0;
                p = ne[p];
            }
            */
            j = tr[j][t];

            int p = j;
            while (p)
            {
                res += cnt[p];
                cnt[p] = 0;//she he 把cnt[e]的用过了之后 res=2 此时再进来一个her 就不能再+he的cnt了,所以cnt[e]用过之后要置0
                p = ne[p];
            }
        }

        printf("%d\n", res);
    }

    return 0;
}