#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
//#define mp make_pair
// #define x first
// #define y second
#define pb push_back
#define szie size
// ifstream fin("data.in");
// #define cin fin
// ofstream fout("data.out");
// #define cout fout

const ll maxn = 1e6 + 5;
ll n, q, r, cnt, opt;
ll v[maxn], dfn[maxn], nfd[maxn], siz[maxn], val[4 * maxn];
vector<ll> edge[maxn];
void dfs(ll u) {
    nfd[++cnt] = u;
    dfn[u] = cnt;
    siz[u] = 1;

    for (auto v : edge[u])
        if (!dfn[v]) {
            dfs(v);
            siz[u] += siz[v];
        }
}
void build(ll l, ll r, ll p) {
    if (l == r) {
        val[p] = v[nfd[l]];
        return;
    }

    ll m = (l + r) >> 1;
    build(l, m, 2 * p);
    build(m + 1, r, 2 * p + 1);
    val[p] += val[2 * p] + val[2 * p + 1];
}
ll query(ll l, ll r, ll p, ll s, ll t) {
    if (l >= s && r <= t)
        return val[p];

    ll m = (l + r) >> 1, res = 0;

    if (s <= m)
        res += query(l, m, 2 * p, s, t);

    if (t > m)
        res += query(m + 1, r, 2 * p + 1, s, t);

    return res;
}
void modify(ll l, ll r, ll p, ll x, ll t) {
    if (l == r) {
        val[p] += t;
        return;
    }

    ll m = (l + r) >> 1;

    if (x <= m)
        modify(l, m, 2 * p, x, t);
    else
        modify(m + 1, r, 2 * p + 1, x, t);

    val[p] = val[2 * p] + val[2 * p + 1];
    return;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> q >> r;

    for (ll i = 1; i <= n; i ++)
        cin >> v[i];

    for (ll i = 1; i < n; i ++) {
        ll u, v;
        cin >> u >> v;
        edge[u].pb(v);
        edge[v].pb(u);
    }

    dfs(r);
    build(1, n, 1);

    while (q --) {
        cin >> opt;

        if (opt == 1) {
            ll a, x;
            cin >> a >> x;
            modify(1, n, 1, dfn[a], x);
        } else {
            ll a;
            cin >> a;
            cout << query(1, n, 1, dfn[a], dfn[a] + siz[a] - 1) << endl;
        }
    }

    return 0;
}

/*
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define endl '\n'
#define int long long
int n, m, r, a[1000005], c[1000005], dfn[1000005], cnt[1000005], idx;
vector<int>v[1000005];
int dfs(int x, int fa) {
    dfn[x] = ++idx;
    cnt[dfn[x]] = 1;

    for (int i = 0; i < v[x].size(); i++) {
        int t = v[x][i];

        if (t != fa)
            cnt[dfn[x]] += dfs(t, x);
    }

    return cnt[dfn[x]];
}
int lowbit(int x) {
    return x & -x;
}
void update(int x, int val) {
    for (int i = x; i <= n; i += lowbit(i))
        c[i] += val;
}
int query(int x) {
    int res = 0;

    for (int i = x; i; i -= lowbit(i))
        res += c[i];

    return res;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m >> r;

    for (int i = 1; i <= n; i++)
        cin >> a[i];

    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        v[x].push_back(y);
        v[y].push_back(x);
    }

    dfs(r, 0);

    for (int i = 1; i <= n; i++)
        update(dfn[i], a[i]);

    while (m--) {
        int op, x, y;
        cin >> op >> x;
        x = dfn[x];

        if (op == 1) {
            cin >> y;
            update(x, y);
        } else
            cout << query(x + cnt[x] - 1) - query(x - 1) << endl;
    }

    return 0;
}
*/