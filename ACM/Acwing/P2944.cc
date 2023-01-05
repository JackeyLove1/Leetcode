# include <iostream>
# include <cstdio>
# include <cstring>
# include <queue>

using namespace std;
const int N = 1e6 + 5;
const int M = 2e6 + 5;
const int inf = 0x3f3f3f3f;

typedef struct {
	int x , y , z , next;
} Edge;
Edge edge[M];
int elast[N] , E = 1;
void add(int x , int y , int z) {
	E ++;
	edge[E].x = x;
	edge[E].y = y;
	edge[E].z = z;
	edge[E].next = elast[x];
	elast[x] = E;
}
int S , T;
int dis[N] , cnt[N];
void bfs(int start) {
	queue<int> q;
	q.push(start);
	dis[start] = 0;
	cnt[S] = 1;
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		for (int i = elast[cur] ; i ; i = edge[i].next) {
			int v = edge[i].y;
			if (dis[v] != -1) continue;
			dis[v] = dis[cur] + 1;
			q.push(v);
			cnt[dis[v]] ++;
		}
	}
}
int cur[N];
int dfs(int u , int flow) {
	if (u == T) return flow;
	int delta = 0;
	for (int i = cur[u] ; i ; i = edge[i].next) {
		cur[u] = i;
		int v = edge[i].y;
		if (edge[i].z > 0 && dis[u] == dis[v] + 1) {
			int temp = dfs(v , min(flow - delta , edge[i].z));
			edge[i].z -= temp;
			edge[i ^ 1].z += temp;
			delta += temp;
			if (delta == flow) return delta;
		}
	}
	if (dis[S] >= T + 1) return delta;
	cur[u] = elast[u];
	if (-- cnt[dis[u]] == 0) dis[S] = T + 1;
	cnt[++ dis[u]] ++;
	return delta;
}
int Isap() {
	int ans = 0;
	memset(cnt , 0 , sizeof cnt);
	memset(dis , -1 , sizeof dis);
	bfs(T);
	for (int i = 0 ; i <= T ; i ++) {
		cur[i] = elast[i];
	}
	while (dis[S] < T + 1) ans += dfs(S , inf);
	return ans;
}
int p , n , m;
int x , y;
bool st[N];
int main() {
	cin >> p >> m >> n;
	S = 0 , T = p << 1 | 1;
	add(S , 1 , inf);
	add(1 , S , 0);
	add(1 , p + 1 , inf);
	add(p + 1 , 1 , 0);
	for (int i = 1 ; i <= m ; i ++) {
		scanf("%d%d" , &x , &y);
		add(x + p , y , inf) , add(y , x + p , 0);
		add(y + p , x , inf) , add(x , y + p , 0);
	}
	for (int i = 1 ; i <= n ; i ++) {
		scanf("%d" , &x);
		st[x] = true;
		add(x , x + p , inf) , add(x + p , x , 0);
		add(x + p , T , inf) , add(T , x + p , 0);
	}
	for (int i = 2 ; i <= p ; i ++) {
		if (!st[i]) add(i , i + p , 1) , add(i + p , i , 0); 
	}
	printf("%d\n" , Isap());
	return 0;
}