/*
#include <iostream>
using namespace std;

typedef unsigned long long ULL;
const int N = 1000010, P = 131;
int n, m;
char s[N];

// p[i]=P^i, h[i]=s[1~i]的hash值
ULL p[N], h[N];

// 预处理 hash函数的前缀和
void init(){
  p[0] = 1, h[0] = 0;
  for(int i = 1; i <= n; i ++){
    p[i] = p[i-1]*P;
    h[i] = h[i-1]*P+s[i];
  }  
}
// 计算s[l~r]的 hash值
ULL get(int l, int r){ 
  return h[r]-h[l-1]*p[r-l+1];
}
// 判断两子串是否相同
bool substr(int l1,int r1,int l2,int r2){
  return get(l1, r1) == get(l2, r2);
}

int main(){
  cin >> n >> m;
  scanf("%s", s + 1);

  init();
  while(m --){
    int a, b, c, d;
    cin >> a >> b >>c >> d;
    if(substr(a,b,c,d)) puts("Yes");
    else puts("No");
  }
  return 0;
}
*/
#include <iostream>
#include <algorithm>

using namespace std;

typedef unsigned long long ULL;

const int N = 100010, P = 131;

int n, m;
char str[N];
ULL h[N], p[N];

ULL get(int l, int r)
{
    return h[r] - h[l - 1] * p[r - l + 1];
}

int main()
{
    scanf("%d%d", &n, &m);
    scanf("%s", str + 1);

    p[0] = 1;
    for (int i = 1; i <= n; i ++ )
    {
        h[i] = h[i - 1] * P + str[i];
        p[i] = p[i - 1] * P;
    }

    while (m -- )
    {
        int l1, r1, l2, r2;
        scanf("%d%d%d%d", &l1, &r1, &l2, &r2);

        if (get(l1, r1) == get(l2, r2)) puts("Yes");
        else puts("No");
    }

    return 0;
}

/*
// string
ull h[N][N], p[N];
string str[N];
constexpr ull P = 131;

inline ull get(int idx, int l, int r) {
    return h[idx][r + 1] - h[idx][l] * p[r - l + 1];
}

inline void init() {
    p[0] = 1;
    for (int i = 1; i < N; ++i) {
        p[i] = p[i - 1] * P;
    }
}

inline void str_hash(int idx) {
    const auto &s = str[idx];
    for (int i = 1; i <= s.size(); i++) {
        h[idx][i] = h[idx][i - 1] * P + s[i - 1];
    }
}
*/