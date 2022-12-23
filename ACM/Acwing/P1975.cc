#include <algorithm>
#include <bits/stdc++.h>
#include <cstddef>
#include <stack>

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
const int N = 1e5 + 100, M = 3e7 + 10;
using ll = long long;
struct Node {
  int l, r;
  int cnt;
};

std::array<Node, M> tr;
int n, m, idx;
int a[N], root[N];

void update(int &u, int l, int r, int x, int v) {
  if (!u)
    u = ++idx;
  tr[u].cnt += v;
  if (l == r)
    return;
  int mid = (l + r) >> 1;
  if (x <= mid)
    update(tr[u].l, l, mid, x, v);
  else
    update(tr[u].r, mid + 1, r, x, v);
}
inline int lowbit(int x) { return x & -x; }
inline void add(int pos, int data, int x) {
  for (; pos <= n; pos += lowbit(pos))
    update(root[pos], 1, n, data, x);
}

int t1 = 0, t2 = 0, q1[N], q2[N];
// 询问root[l, r]内值大于x的数目
ll queryLarge(int l, int r, int x) {
  t1 = 0, t2 = 0;
  for (int i = l - 1; i; i -= lowbit(i))
    q1[++t1] = root[i];
  for (int i = r; i; i -= lowbit(i))
    q2[++t2] = root[i];
  l = 1, r = n;
  ll sum = 0;
  while (l < r) {
    int mid = l + r >> 1;
    if (x > mid) {
      for (int i = 1; i <= t1; ++i)
        q1[i] = tr[q1[i]].r;
      for (int i = 1; i <= t2; ++i)
        q2[i] = tr[q2[i]].r;
      l = mid + 1;
    } else {
      for (int i = 1; i <= t1; ++i)
        sum -= tr[tr[q1[i]].r].cnt;
      for (int i = 1; i <= t2; ++i)
        sum += tr[tr[q2[i]].r].cnt;
      for (int i = 1; i <= t1; ++i)
        q1[i] = tr[q1[i]].l;
      for (int i = 1; i <= t2; ++i)
        q2[i] = tr[q2[i]].l;
      r = mid;
    }
  }
  return sum;
}

ll querySmall(int l, int r, int x) {
  t1 = 0, t2 = 0;
  for (int i = l - 1; i; i -= lowbit(i))
    q1[++t1] = root[i];
  for (int i = r; i; i -= lowbit(i))
    q2[++t2] = root[i];
  l = 1, r = n;
  ll sum = 0;
  while (l < r) {
    int mid = l + r >> 1;
    if (x > mid) {
      for (int i = 1; i <= t1; ++i)
        sum -= tr[tr[q1[i]].l].cnt;
      for (int i = 1; i <= t2; ++i)
        sum += tr[tr[q2[i]].l].cnt;
      for (int i = 1; i <= t1; ++i)
        q1[i] = tr[q1[i]].r;
      for (int i = 1; i <= t2; ++i)
        q2[i] = tr[q2[i]].r;
      l = mid + 1;
    } else {
      for (int i = 1; i <= t1; ++i)
        q1[i] = tr[q1[i]].l;
      for (int i = 1; i <= t2; ++i)
        q2[i] = tr[q2[i]].l;
      r = mid;
    }
  }
  return sum;
}

inline void addPos(ll &sum, int pos) {
  sum += queryLarge(1, pos - 1, a[pos]);
  sum += querySmall(pos + 1, n, a[pos]);
  add(pos, a[pos], 1);
  // cout << "add pos: " << pos << " v: " << a[pos] << " sum: " << sum << endl;
}
inline void delPos(ll &sum, int pos) {
  sum -= queryLarge(1, pos - 1, a[pos]);
  sum -= querySmall(pos + 1, n, a[pos]);
  add(pos, a[pos], -1);
  // cout << "del pos: " << pos << " v: " << a[pos] << " sum: " << sum << endl;
}

int main() {
  fhj();
  cin >> n;
  ll sum = 0;
  vector<int> nums;
  nums.reserve(n);
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    nums.push_back(a[i]);
  }
  sort(nums.begin(), nums.end());
  nums.erase(unique(nums.begin(), nums.end()), nums.end());
  for (int i = 1; i <= n; ++i) {
    a[i] = lower_bound(nums.begin(), nums.end(), a[i]) - nums.begin() + 1;
    // pos[a[i]] = i;
    sum += queryLarge(1, i - 1, a[i]);
    add(i, a[i], 1);
    // cout << "a[" << i << "], sum = " << sum << endl;
  }
  cout << sum << endl;
  cin >> m;
  for (int i = 1; i <= m; ++i) {
    int posa, posb;
    cin >> posa >> posb;
    if (posa > posb) std::swap(posa, posb);
    delPos(sum, posa), delPos(sum, posb);
    std::swap(a[posa], a[posb]);
    addPos(sum, posa), addPos(sum, posb);
    cout << sum << endl;
  }
  return 0;
}
