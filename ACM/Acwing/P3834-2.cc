#include <array>
#include <bits/stdc++.h>
#include <cstring>

using namespace std;
constexpr bool debug = true;
const int N = 2e5+10, M = 10010;
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
  Node() : l(0), r(0), cnt(0),val(0) {}
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

int insert(int pre, int l, int r, int x){
    int cur = ++idx;
    tr[cur] = tr[pre];
    if(l == r){
        tr[cur].cnt++;
        return cur;
    }
    int mid = l + r >> 1;
    if(x <= mid) tr[cur].l = insert(tr[pre].l, l, mid, x);
    else tr[cur].r = insert(tr[pre].r, mid + 1, r, x);
    tr[cur].cnt = tr[tr[cur].l].cnt + tr[tr[cur].r].cnt;
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


int query(int cur, int pre, int l, int r, int k){
    if (l == r) return r;
    int cnt = tr[tr[cur].l].cnt - tr[tr[pre].l].cnt;
    int mid = l + r >> 1;
    if (k <= cnt) return query(tr[cur].l, tr[pre].l, l, mid, k);
    else return query(tr[cur].r, tr[pre].r, mid + 1, r, k - cnt);
}

int main() {
  fhj();
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    nums.push_back(a[i]);
  }
  sort(nums.begin(), nums.end());
  nums.erase(unique(nums.begin(), nums.end()), nums.end());
  root[0] = build(1, n);
  for (int i = 1; i <= n; ++i){
    root[i] = insert(root[i - 1], 1, n, find(a[i]) + 1);
  }
    for (int i = 1; i <= m; i++) {
        int l, r, k;
        cin >> l >> r >> k;
        cout << nums[query(root[r], root[l - 1], 1, n, k) - 1] << endl;
    }
  return 0;
}