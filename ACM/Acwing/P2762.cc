#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int A = 1e5 + 11;
const int B = 1e6 + 11;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

inline int read() {
	char c = getchar(); int x = 0, f = 1;
	for ( ; !isdigit(c); c = getchar()) if(c == '-') f = -1;
	for ( ; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
	return x * f;
}

int m, n, cnt, opt, S, T, ans, head[A], d[A], q[A];
struct node { int from, to, nxt, val; } e[A];

inline void add(int from, int to, int val) {
	e[cnt].to = to;
	e[cnt].val = val;
	e[cnt].nxt = head[from];
	head[from] = cnt++;
}

inline bool makelevel(int s, int t) {
	memset(d, 0, sizeof(d));
	memset(q, 0, sizeof(q));
	int l = 0, r = 0;
	d[s] = 1; q[r++] = s;
	while (l < r) {
		int x = q[l++];
		if (x == t) return true;
		for (int i = head[x]; i != -1; i = e[i].nxt) {
			int to = e[i].to;
			if (d[to] == 0 && e[i].val > 0) {
				d[to] = d[x] + 1;
				q[r++] = e[i].to;
			}
		}
	}
	return false;
}

int dfs(int x, int flow, int t) {
	if (x == t) return flow;
	int sum = 0;
	for (int i = head[x]; i != -1; i = e[i].nxt) {
		int to = e[i].to;
		if (d[to] == d[x] + 1 && e[i].val > 0) {
			int tmp = dfs(to, min(flow - sum, e[i].val), t);
			e[i].val -= tmp, e[i ^ 1].val += tmp;
			sum += tmp;
			if (sum == flow) return sum;
		}
	}
	return sum;
}

int main() {
	memset(head, -1, sizeof(head));
	m = read(), n = read();
	int S = 0, T = 555;
	int w, tot = 0, x;
	for (int i = 1; i <= m; i++) {
		scanf("%d", &w), tot += w;
		add(S, i, w), add(i, S, 0);
		while (getchar() == ' ') {
			scanf("%d", &x);
			add(i, x + m, inf);
			add(x + m, i, 0);
		}
	}
	for (int i = 1; i <= n; i++) {
		x = read();
		add(i + m, T, x), add(T, i + m, 0);
	}
	while (makelevel(S, T)) ans += dfs(S, inf, T);
	ans = tot - ans;
	for (int i = 1; i <= m; i++) if (d[i]) cout << i << ' '; puts("");
	for (int i = 1; i <= n; i++) if (d[i + m]) cout << i << ' '; puts("");
	cout << ans << '\n';
	return 0;
}