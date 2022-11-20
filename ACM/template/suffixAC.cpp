/*
#pragma GCC optimize(2)

#include <bits/stdc++.h>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 2000010;
using ll = long long;
int tot = 1, last = 1;
struct Node {
    int len, fa;
    int ch[26];
} node[N];
char str[N];
ll f[N], ans;
int h[N], e[N], ne[N], idx;

inline void extend(int c) {
    int p = last, np = last = ++tot;
    f[tot] = 1;
    node[np].len = node[p].len + 1;
    for (; p && !node[p].ch[c]; p = node[p].fa) node[p].ch[c] = np;
    if (!p) node[np].fa = 1;
    else {
        int q = node[p].ch[c];
        if (node[q].len == node[p].len + 1) node[np].fa = q;
        else {
            int nq = ++tot;
            node[nq] = node[q], node[nq].len = node[p].len + 1;
            node[q].fa = node[np].fa = nq;
            for (; p && node[p].ch[c] == q; p = node[p].fa) node[p].ch[c] = nq;
        }
    }
}

inline void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void dfs(int u) {
    for (int i = h[u]; ~i; i = ne[i]) {
        dfs(e[i]);
        f[u] += f[e[i]];
    }
    if (f[u] > 1) ans = max(ans, f[u] * node[u].len);
}

int main() {
    scanf("%s", str);
    for (int i = 0; str[i]; i++) extend(str[i] - 'a');
    memset(h, -1, sizeof h);
    for (int i = 2; i <= tot; i++) add(node[i].fa, i);
    dfs(1);
    printf("%lld\n", ans);
    return 0;
}
*/

/*
// Luogu P3804 【模板】后缀自动机 (SAM)
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long LL;
const int N=2e6+10;
char str[N];
vector<int> e[N];//邻接表
LL cnt[N],ans;
int tot=1,np=1;
//fa链接边终点,ch转移边终点,len最长串长度
int fa[N],ch[N][26],len[N];

void extend(int c){
  //p回跳指针, np新点, q链接点, nq新链接点
  int p=np; np=++tot;//p指向旧点, np是新点
  len[np]=len[p]+1; cnt[np]=1;//子串出现次数 
  //p沿链接边回跳，从旧点向新点建转移边
  for(;p&&!ch[p][c];p=fa[p])ch[p][c]=np;
  
  //1.如果c是新字符，从新点向根节点建链接边
  if(p==0)fa[np]=1;
  else{//如果c是旧字符
    int q=ch[p][c];//q是链接点
    //2.若链接点合法，从新点向q建链接边
    if(len[q]==len[p]+1)fa[np]=q;
    //3.若链接点不合法，则裂开q点，重建两类边
    else{
      int nq=++tot;//nq是新链接点
      len[nq]=len[p]+1;
      //重建nq,q,np的链接边
      fa[nq]=fa[q]; fa[q]=nq; fa[np]=nq;
      //指向q的转移边改为指向nq
      for(;p&&ch[p][c]==q;p=fa[p])ch[p][c]=nq;
      //从q发出的转移边复制给nq
      memcpy(ch[nq],ch[q],sizeof(ch[q]));
    }
  }
}
void dfs(int u){ 
  for(auto v : e[u]){
    dfs(v);
    cnt[u]+=cnt[v];
  }
  if(cnt[u]>1)ans=max(ans,cnt[u]*len[u]);
}
int main(){
  scanf("%s",str);
  for(int i=0;str[i];i++)extend(str[i]-'a');
  for(int i=2;i<=tot;i++)e[fa[i]].push_back(i);
  dfs(1);
  printf("%lld\n",ans);
  return 0;
}
*/
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 2000010;

int tot = 1, last = 1;
struct Node
{
    int len, fa;
    // len最长后缀字串长度，fa父节点（状态集合）
    int ch[26];
    // 转移指针
}node[N];
char str[N]; // 需要插入的字符串
LL f[N], ans;
int h[N], e[N], ne[N], idx;

void extend(int c)
{
    // last是未加入此字符前最长的前缀（整个串）所属的节点的编号
    // tot 是当前后缀自动机节点的总数
    int p = last, np = last = ++ tot;
    f[tot] = 1;
    node[np].len = node[p].len + 1;
    // 新加入了一位字符c（减了'a' ）是为了方便塞进边里，
    // 可类比trietrie里对字符的处理）。我们设未加入cc前的原串为旧串，
    // 加入cc后的原串为新串。显然，此时新串的最长前缀（整个串）所属的节点
    // 显然不在原图中（因为原来的所有endposendpos都不可能包含这一位）。
    // 而旧串的最长前缀就变成了新串的次大前缀。所以我们用pp记录新串次大前缀（
    // 原串的最大前缀）所属的节点，然后新建一个节点npnp（tottot加一），
    // 存新的最大前缀所属的类。而len(np)len(np)肯定就是新串的长度，
    // 即len(p)+1len(p)+1

    // 注意一下，加入cc后，endposendpos可能发生变化的字符串只有新串的后缀
    // （或者说，旧串的后缀加cc）（它们无论在旧串出现与否，在新串中出现的次数
    // 一定会比在旧串中多11）。所以我们的任务就是处理好这些endposendpos发生
    // 变化的字符串（具体做法是遍历旧串后缀（事实上是遍历旧串的后缀自动机的终止
    // 节点），看看它们加cc后endposendpos有没有改变）。
    for (; p && !node[p].ch[c]; p = node[p].fa) node[p].ch[c] = np;
    // 接下来，我们进行一个循环操作。这个循环操作进行下去的条件是：
    // !dian[p].ch[c]!dian[p].ch[c]（!p!p只是防止其跳出根节点），
    // 即pp没有一条cc的出边。而pp每一次循环后会跳到dian[p].fadian[p].fa，
    // 即fa(p)fa(p)。首先我们得知道往上跳到底是干什么。
    // 我们知道存在父子关系节点包含的子串有后缀关系。那么，
    // 这个pp跳fa(p)fa(p)操作的意思即：**一个是longest(p)longest(p)
    // （还记得longestlongest是什么意思吗？定义在结论55的证明下面）的后缀，
    // 且与longest(p)longest(p)所属类不同的最长串所属的类。
    // （这里的longestlongest改成shortestshortest也无妨）
    // 虽然这里有点绕，但是却对下面的理解尤为重要，请大家熟记。
    // 因为由一个节点往外连一条边就等于允许到达此节点的所有字符串往尾部添加一个新的字符。
    // 并且，由于len(fa(i))+1=minlen(i)len(fa(i))+1=minlen(i)，
    // 因此对于ii和fa(i)fa(i)，它们包含的子串的长度从大到小排序时也是连续的。
    // 所以我们把每一个节点想象成所有到达它的字符串的集合。
    // 那么，这个跳fa(i)fa(i)的操作可以理解为压缩地遍历一个串的所有后缀。
    // （之后会多次直接引用这个思想）在这里，即遍历旧串的所有后缀。
    if (!p) node[np].fa = 1;
    // 如果已经遍历完了旧串的后缀且它们加cc一个都不是旧串的子串
    // （它们在新串中的endposendpos都是\{n\}{n}），就说明我们已经处理完了新串的所有后缀，
    // 完成了任务。所以npnp的fafa直接设为11，
    // 表示第一个与新串最长前缀endposendpos不同且为新串最长前缀的后缀的字符串是空串。
    else
    {
        int q = node[p].ch[c];
        if (node[q].len == node[p].len + 1) node[np].fa = q;
        else
        {
            int nq = ++ tot;
            node[nq] = node[q], node[nq].len = node[p].len + 1;
            node[q].fa = node[np].fa = nq;
            for (; p && node[p].ch[c] == q; p = node[p].fa) node[p].ch[c] = nq;
        }
    }
}

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

void dfs(int u)
{
    for (int i = h[u]; ~i; i = ne[i])
    {
        dfs(e[i]);
        f[u] += f[e[i]];
    }
    if (f[u] > 1) ans = max(ans, f[u] * node[u].len);
}

int main()
{
    scanf("%s", str);
    for (int i = 0; str[i]; i ++ ) extend(str[i] - 'a');
    memset(h, -1, sizeof h);
    for (int i = 2; i <= tot; i ++ ) add(node[i].fa, i);
    dfs(1);
    printf("%lld\n", ans);

    return 0;
}
