#include <bits/stdc++.h>
#include <cstddef>

using namespace std;

inline void fhj() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
}

template <typename T> void read(T &t) {
  t = 0;
  bool fl = true;
  char p = getchar();
  while (!isdigit(p)) {
    if (p == '-')
      fl = false;
    p = getchar();
  }
  do {
    (t *= 10) += p - 48;
    p = getchar();
  } while (isdigit(p));
  if (!fl)
    t = -t;
}
const int N = 10005, M = N * 32 * 14;

int n, m;
int a[N];
vector<int> nums;

struct Node {
  int l, r;
  int cnt;
} tr[M];

// int lson[M], rson[M], cnt[M];
int root[N], idx;

int find(int x) // get_id
{
  return lower_bound(nums.begin(), nums.end(), x) - nums.begin();
}

int build(int l, int r) {
  int p = ++idx;
  if (l == r)
    return p;
  int mid = l + r >> 1;
  // lson[p] = build(l, mid), rson[p] = build(mid + 1, r);
  tr[p].l = build(l, mid), tr[p].r = build(mid+1, r);
  return p;
}

void insert(int &p, int l, int r, int x) {
  if (!p)
    p = ++idx;
  tr[p].cnt++;
  if (l == r)
    return;
  int mid = l + r >> 1;
  if (x <= mid)
    insert(tr[p].l, l, mid, x);
  else
    insert(tr[p].r, mid + 1, r, x);
}



void del(int p, int l, int r, int x) {
  tr[p].cnt--;
  if (l == r)
    return;
  int mid = l + r >> 1;
  if (x <= mid)
    del(tr[p].l, l, mid, x);
  else
    del(tr[p].r, mid + 1, r, x);
}

const int st = 0, ed = 1e9;
inline int lowbit(int x) { return x & -x; }

inline void add(int x, int v) {
  for (int i = x; i <= n; i += lowbit(i))
    insert(root[i], st, ed, v);
}

inline void change(int x, int v) {
  for (int i = x; i <= n; i += lowbit(i)) {
    insert(root[i], st, ed, v);
    del(root[i], st, ed, a[x]);
  }
  a[x] = v;
}
int t1 = 0, t2 = 0, q1[N], q2[N];

int query(int l, int r, int k) {
  if (l == r)
    return l;
  int lsize = 0;
  for (int i = 1; i <= t1; ++i)
    lsize += tr[tr[q1[i]].l].cnt;
  for (int i = 1; i <= t2; ++i)
    lsize -= tr[tr[q2[i]].l].cnt;
  int mid = l + r >> 1;
  if (k <= lsize) {
    for (int i = 1; i <= t1; ++i)
      q1[i] = tr[q1[i]].l;
    for (int i = 1; i <= t2; ++i)
      q2[i] = tr[q2[i]].l;
    return query(l, mid, k);
  } else {
    for (int i = 1; i <= t1; ++i)
      q1[i] = tr[q1[i]].r;
    for (int i = 1; i <= t2; ++i)
      q2[i] = tr[q2[i]].r;
    return query(mid + 1, r, k - lsize);
  }
}


int main() {
  fhj();
  cin >> n >> m;
  // root[0] = build(st, ed);
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    add(i, a[i]);
  }
  for (int i = 1; i <= m; ++i) {
    string op;
    cin >> op;
    if (op == "Q") {
      int x, y, z;
      cin >> x >> y >> z;
      t1 = t2 = 0;
      for (int j = y; j; j -= lowbit(j))
        q1[++t1] = root[j];
      for (int j = x - 1; j; j -= lowbit(j))
        q2[++t2] = root[j];
      cout << query(st, ed, z) << endl;
    } else {
      int x, y;
      cin >> x >> y;
      change(x, y);
    }
  }
  return 0;
}