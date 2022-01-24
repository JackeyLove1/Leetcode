#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
const int N = 10010, S = 55, M = 1000010;
int trie[N * S][26], cnt[N * S], idx;  //cnt[i]表示以i + 'a'为结尾的个数   idx为当前树节点的指针
char str[M]; //以"/0"为结尾，所以不用每次都更新
int que[N * S], fail[N * S]; //que[]表示队列  ， fail[]为失配指针(下标表示树节点的指针)  
int n;


void insert(){
    int p = 0;
    for(int i = 0;str[i];++i){
        int u = str[i] - 'a';
        if(!trie[p][u]) trie[p][u] = ++idx;
        p = trie[p][u];
    }
    cnt[p]++;
}

void build(){  //构造fail数组，bfs
    int hh = 0,tt = -1;  //队头和队尾指针
    //根节点是第0层
    for(int i = 0;i < 26;++i){  //第一层的元素全部入队
        if(trie[0][i]) que[++tt] = trie[0][i];
    }
    while(hh <= tt){
        int ans = que[hh++];
        //枚举当前队头的26个分支
        for(int i = 0;i < 26;++i){
            if(trie[ans][i]){  //如果存在我们就让它的fail指针指向他父亲节点 a 的 fail 指针指向的那个节点（根）的具有相同字母的子节点
                fail[trie[ans][i]] = trie[fail[ans]][i];
                que[++tt] = trie[ans][i];  //当前节点入队
            }else{  //就算不存在，不跳，他的值等于父节点的fail只想的具有相同字母的子节点
                trie[ans][i] = trie[fail[ans]][i]; 
            }
        }
    }
}



int main(){
    int t;
    cin >> t;
    while(t--){

        memset(cnt,0,sizeof cnt);
        memset(trie,0,sizeof trie);
        memset(fail,0,sizeof fail);
        idx = 0;
      cin >> n;
      for(int i = 0;i < n;++i){
          scanf("%s",str);
          insert();
      }

      build();
      scanf("%s",str);

      int res = 0;  
      //j记录当前树节点的指针，初始是根节点 
      for(int i = 0,j = 0;str[i];++i){  //枚举总串str的每一个字母
          int u = str[i] - 'a';
          j = trie[j][u];  //跳到下一个树节点
          int p = j; //每次从当前树节点开始

          //fail[p]所指向的树节点如果有结尾标记可以直接算上，因为当前模式串后缀和fail指针指向的模式串部分前缀相同，所以是包含在里面的
          while(p){  //假如模式串"she"可以匹配上，那么匹配到"e"的时候，用fail指针跳到模式串"he"的"e"，那么也一定能够匹配"he"
             res += cnt[p];
             cnt[p] = 0;  //去除标记
             p = fail[p];
          }
      }
      cout << res << endl;
    }
    return 0;
}
