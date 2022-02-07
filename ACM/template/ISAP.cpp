int read() {
	int x=0,f=1;
	char c=getchar();
	for (;!isdigit(c);c=getchar()) if (c=='-') f=-1;
	for (;isdigit(c);c=getchar()) x=x*10+c-'0';
	return x*f;
}

typedef long long ll;
const int N = 5007, M = 5e3 + 7, INF = 2e9 + 7;

int head[N], ver[M], nex[M], edge[M], cur[N], tot;
int n, m;
int gap[N], deep[N];
int q[M];
int cnt;
void add(int x, int y, int z){
    ver[++ tot] = y;
    edge[tot] = z;
    nex[tot] = head[x];
    head[x] = tot;
    ver[++ tot] = x;
    edge[tot] = 0;
    nex[tot] = head[y];
    head[y] = tot;
}

void init(int s, int t){//!只需要O(n+m)倒序从t到s,bfs求一次增广路即可
    memset(gap, 0, sizeof gap);
    memset(deep, 0, sizeof deep);

    ++gap[deep[t] = 1];//! ! !

    for(int i = 1;i <= n; ++ i)
        cur[i] = head[i];
    //memcpy(cur, head, sizeof head);
    int hh = 0, tt = -1;
    q[hh = tt = 1] = t;

    while(hh <= tt){
        int x = q[hh ++ ];//if(hh == M)hh = 0;
        for(int i = head[x]; ~i; i = nex[i]){//这里y要写两次,因为i变了
            int y = ver[i];
            if(!deep[y])
                ++gap[deep[y] = deep[x] + 1], q[++ tt] = y;//if(tt == M)tt = 0;
        }
    }
}

int dfs(int x, int s, int t, int mi){
    if(x == t)return mi;
    int flow = 0;
    for(int &i = cur[x]; ~i; i = nex[i]){//&i = cur[x] -- 弧优化
        int y = ver[i];
        if(deep[x] == deep[y] + 1){//因为倒着走的嘛
            int k = dfs(y, s, t, min(mi, edge[i]));
            flow += k, mi -= k, edge[i] -= k, edge[i ^ 1] += k;
            if(!mi)return flow;
        }
    }
    if(!(--gap[deep[x]]))deep[s] = n + 1;//如果deep[x]这一层走完了就标记一下， 可以结束了
    ++gap[++deep[x]], cur[x] = head[x];
    return flow;
}
// augment v. 增加
int ISAP(int s, int t){
    init(s, t);
    //cout << "ok" << cnt ++ << endl;
    int res = dfs(s, s, t, INF);//必须要先跑一次，因为已经跑过一次增广路了。
    while(deep[s] <= n)
        res += dfs(s, s, t, INF);
    return res;
}

int main(){
    while(~scanf("%d%d", &m, &n)){
        tot = 0, memset(head, -1, sizeof head);
        for(int i= 1;i <= m; ++ i){
            int x = read(), y = read(), z = read();
            add(x, y, z);
        }
        int ans = ISAP(1, n);
        printf("%d\n", ans);
    }
    return 0;
}
