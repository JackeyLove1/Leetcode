#include <cstring>
#include <iostream>
#include <queue>

using namespace std;

const int N = 2e3 + 10, M = 1e4 + 10;

int n, m;
int head[N], e[M], ne[M], w[M], idx;
bool st[N];
int dist[N];
int cnt[N]; //cnt[x] 表示 当前从1-x的最短路的边数

void add(int a, int b, int c)
{
    e[idx] = b;
    ne[idx] = head[a];
    w[idx] = c;
    head[a] = idx++;
}

bool spfa(){
    // 这里不需要初始化dist数组为 正无穷/初始化的原因是， 如果存在负环， 那么dist不管初始化为多少， 都会被更新
    queue<int> q;
    //不仅仅是1了， 因为点1可能到不了有负环的点， 因此把所有点都加入队列
    for(int i=1;i<=n;i++){
        q.push(i);
        st[i]=true;
    }
    while(q.size()){
        int t = q.front();
        q.pop();
        st[t]=false;
        for(int i = head[t];i!=-1; i=ne[i]){
            int j = e[i];
            if(dist[j]>dist[t]+w[i]){
                dist[j] = dist[t]+w[i];
                cnt[j] = cnt[t]+1;
                if(cnt[j]>=n){
                    return true;
                }
                if(!st[j]){
                    q.push(j);
                    st[j]=true; // ++cnt[j] > n
                }
            }
        }
    }
    return false;
}

int main()
{
    cin >> n >> m;
    memset(head, -1, sizeof head);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
    }

    if (spfa()) {
        cout << "Yes" << endl;
    }
    else {
        cout << "No" << endl;
    }
    return 0;
}