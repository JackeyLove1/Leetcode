#include <bits/stdc++.h>
using namespace std;
// 除 RMQ 以外，还有其它的“可重复贡献问题”。例如“区间按位和”、“区间按位或”、“区间 GCD”，ST 表都能高效地解决

template <typename T>
class SparseTable {
  using VT = vector<T>;
  using VVT = vector<VT>;
  using func_type = function<T(const T &, const T &)>;

  VVT ST;

  static T default_func(const T &t1, const T &t2) { return max(t1, t2); }

  func_type op;

 public:
  SparseTable(const vector<T> &v, func_type _func = default_func) {
    op = _func;
    int len = v.size(), l1 = ceil(log2(len)) + 1;
    ST.assign(len, VT(l1, 0));
    for (int i = 0; i < len; ++i) {
      ST[i][0] = v[i];
    }
    for (int j = 1; j < l1; ++j) {
      int pj = (1 << (j - 1));
      for (int i = 0; i + pj < len; ++i) {
        ST[i][j] = op(ST[i][j - 1], ST[i + (1 << (j - 1))][j - 1]);
      }
    }
  }

  T query(int l, int r) {
    int lt = r - l + 1;
    int q = ceil(log2(lt)) - 1;
    return op(ST[l][q], ST[r - (1 << q) + 1][q]);
  }
};
/*
void pre() {  // 准备工作，初始化
  Logn[1] = 0;
  Logn[2] = 1;
  for (int i = 3; i < maxn; i++) {
    Logn[i] = Logn[i / 2] + 1;
  }
}

int main() {
  int n = read(), m = read();
  for (int i = 1; i <= n; i++) f[i][0] = read();
  pre();
  for (int j = 1; j <= logn; j++)
    for (int i = 1; i + (1 << j) - 1 <= n; i++)
      f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);  // ST表具体实现
  for (int i = 1; i <= m; i++) {
    int x = read(), y = read();
    int s = Logn[y - x + 1];
    printf("%d\n", max(f[x][s], f[y - (1 << s) + 1][s]));
  }
  return 0;
}

void ST_build(int n){
    for(int j = 1; (1<<j) <= n; j++)
        for(int i = 1; i+(1<<j)-1 <= n ; i++)
            dp[i][j] = dp[i][j-1]|dp[i+(1<<(j-1))][j-1];
}

int query(int l, int r){
    int cnt = log2(r-l+1), len = 1<<cnt;
    return dp[l][cnt]|dp[r-len+1][cnt];
}

*/