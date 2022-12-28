#include <stdio.h>
#include <iostream>
#include <algorithm>
const int N = 1e5, INF = 1e9;
using namespace std;

int n, m, rt, ch[N + 5][2], fa[N + 5], v[N + 5], sz[N + 5], flag[N + 5];

void maintain(int p) {sz[p] = sz[ch[p][0]] + sz[ch[p][1]] + 1;}
void pushdown(int p) {
	if (flag[p]) {
		if (ch[p][0])flag[ch[p][0]] ^= 1;
		if (ch[p][1])flag[ch[p][1]] ^= 1;
		swap(ch[p][0], ch[p][1]); flag[p] = 0;
	}
}

int get(int x) {return x == ch[fa[x]][1];}

void rotate(int x) {
	int y = fa[x], z = fa[y], k = get(x);
	// pushdown(y); pushdown(x);
	ch[z][get(y)] = x; fa[x] = z;
	 ch[y][k] = ch[x][k^1];fa[ch[x][k^1]] = y;
	ch[x][k^1] = y; fa[y] = x;
	maintain(y); maintain(x);
}
void splay(int x, int k) {
	while(fa[x] != k) {
		int y = fa[x], z = fa[y];
		// cout << x << ' ' << y << ' ' << z << endl;
		pushdown(z); pushdown(y); pushdown(x);
		if (z != k) {
			if (get(y) != get(x)) rotate(x);
			else rotate(y);
		}
		rotate(x);
	}
	if (!k) rt = x;
}

void build(int &p, int l, int r) {
	if (l > r) return;
	int mid = l + r >> 1; p =  mid;
	if (l == r) {
		sz[p] = 1;
		return;
	}
	if (l < mid) {
		build(ch[p][0], l, mid - 1);
		fa[ch[p][0]] = p;
	}
	if (r > mid) {
		build(ch[p][1], mid + 1, r);
		fa[ch[p][1]] = p;
	}
	maintain(p);
}

int get_k(int k) {
	int p = rt;
	while(1) {
		pushdown(p);
		if (sz[ch[p][0]] >= k && ch[p][0]) p = ch[p][0];
		else {
			k -= sz[ch[p][0]] + 1;
			if (k == 0) return p;
			p = ch[p][1]; 
		}
	}
}

struct T{
	int x, pos;
	bool operator < (const T &b) {
		return (x == b.x ? pos < b.pos : x < b.x);
	}
}p[N + 5];

int main() {
	// freopen("t.in", "r", stdin);
	scanf("%d", &n); p[1] = T{-INF, 1}; p[n + 2] = T{INF, n + 2};
	for(int i = 2; i <= n + 1; i++) {
		scanf("%d", &p[i].x);
		p[i].pos = i;
	}
	sort(p + 2, p + n + 2);
	build(rt, 1, n + 2);
	for(int i = 2; i <= n; ++i) {
		splay(p[i].pos, 0);
		int ans = sz[ch[rt][0]];
		printf("%d ", ans);
		int L = get_k(i - 1), R = get_k(ans + 2);
		splay(L, 0); splay(R, L);
		flag[ch[R][0]] ^= 1;
	}
	printf("%d\n", n);
	return 0;
}