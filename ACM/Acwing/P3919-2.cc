#include <array>
#include <bits/stdc++.h>
#include <cstring>

using namespace std;
constexpr bool debug = true;
const int N = 1e6 + 100, M = 10010;
inline void fhj() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
}
int n, m;
int a[N];
vector<int> nums;

class Node {
public:
  int l, r;
  int cnt, val;
  Node() : l(0), r(0), cnt(0) {}
};
std::array<Node, N << 5> tr;

int root[N], idx;

int find(int x) // get_id
{
  return lower_bound(nums.begin(), nums.end(), x) - nums.begin();
}

int build(int l, int r) {
  int p = ++idx;
  if (l == r) {
    tr[p].val = a[l];
    return p;
  }
  int mid = l + r >> 1;
  tr[p].l = build(l, mid), tr[p].r = build(mid + 1, r);
  return p;
}
/*
int insert(int p, int l, int r, int x)
{
    int q = ++ idx;
    tr[q] = tr[p];
    if (l == r)
    {
        tr[q].cnt ++ ;
        return q;
    }
    int mid = l + r >> 1;
    if (x <= mid) tr[q].l = insert(tr[p].l, l, mid, x);
    else tr[q].r = insert(tr[p].r, mid + 1, r, x);
    tr[q].cnt = tr[tr[q].l].cnt + tr[tr[q].r].cnt;
    return q;
}
*/
inline void pushup(int u) {
  auto &rt = tr[u], &lson = tr[tr[u].l], &rson = tr[tr[u].r];
}

int insert(int pre, int l, int r, int pos, int x) {
  int cur = ++idx;
  tr[cur] = tr[pre];
  if (l == r) {
    tr[cur].val = x;
    return cur;
  }
  int mid = l + r >> 1;
  if (pos <= mid)
    tr[cur].l = insert(tr[pre].l, l, mid, pos, x);
  else
    tr[cur].r = insert(tr[pre].r, mid + 1, r, pos, x);
  // pushup(cur);
  return cur;
}

/*
int query(int q, int p, int l, int r, int k)
{
    if (l == r) return r;
    int cnt = tr[tr[q].l].cnt - tr[tr[p].l].cnt;
    int mid = l + r >> 1;
    if (k <= cnt) return query(tr[q].l, tr[p].l, l, mid, k);
    else return query(tr[q].r, tr[p].r, mid + 1, r, k - cnt);
}
*/
int query(int pre, int l, int r, int x) {
  if (l == r)
    return tr[pre].val;
  int mid = l + r >> 1;
  if (x <= mid)
    return query(tr[pre].l, l, mid, x);
  else
    return query(tr[pre].r, mid + 1, r, x);
}

int main() {
  fhj();
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    // nums.push_back(a[i]);
  }
  // sort(nums.begin(), nums.end());
  // nums.erase(unique(nums.begin(), nums.end()), nums.end());
  root[0] = build(1, n);
  for (int i = 1; i <= m; i++) {
    int v, op, loc, val;
    cin >> v >> op;
    if (op == 1) {
      cin >> loc >> val;
      root[i] = insert(root[v], 1, n, loc, val);
    } else {
      cin >> loc;
      cout << query(root[v], 1, n, loc) << endl;
      root[i] = root[v];
    }
  }
  return 0;
}