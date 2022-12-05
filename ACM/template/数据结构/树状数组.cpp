/*
int t[N],a[N];
void update(int i,int x)//将位置i的值加上x
{
    while(i<=n) t[i]+=x,i+=i&(-i);
}
int query(int i)//查询区间[1,i]的和
{
    int res=0;
    while(i) res+=t[i],i-=i&(-i);
    return res;
}
int query(int l,int r)//查询区间[l,r]的和
{
    return query(r)-query(l-1);
}
void build()
{
    for(int i=1;i<=n;i++) update(i,a[i]);//树状数组的建立相当于依次添加
}
void build()
{
    for(int i=1;i<=n;i++)
    {
        t[i]+=a[i];
        int j=i+i&(-i);
        if(j<=n) t[j]+=t[i];
    }
}
*/
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 100010;

int n, m;
int a[N];
LL tr[N];

int lowbit(int x)
{
    return x & -x;
}

void add(int x, int c)
{
    for (int i = x; i <= n; i += lowbit(i)) tr[i] += c;
}

LL sum(int x)
{
    LL res = 0;
    for (int i = x; i; i -= lowbit(i)) res += tr[i];
    return res;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i ++ ) scanf("%d", &a[i]);

// 创建求和树状数组时，加入数据的形式是差分的形式
    for (int i = 1; i <= n; i ++ ) add(i, a[i] - a[i - 1]);

    while (m -- )
    {
        char op[2];
        int l, r, d;
        scanf("%s%d", op, &l);
        if (*op == 'C')
        {
            scanf("%d%d", &r, &d);
            add(l, d), add(r + 1, -d);
        }
        else
        {
            printf("%lld\n", sum(l));
        }
    }

    return 0;
}

// 维护区间最大值
typedef long long ll;
const int Maxn = 2e5+10;
 
int a[Maxn], h[Maxn], n;  // a[] 数列的值，h[] 区间最大值
 
void add (int x, int val) {
	while (x <= n) {
		h[x] = max (h[x], val); 
		x += x&(-x);
	}
}
 
int query (int L, int R) {
	int ret = 0, len = R-L+1;
	while (len && R) {  // len 是当前还需要判断的范围长度，R是对应区间最大值的下标
		if (len < (R&(-R))) {
			ret = max (ret, a[R]);
			R--; len--;
		} else {
			ret = max (ret, h[R]);
			len -= (R&(-R)); // 不断的缩短要判断的区间长度
			R -= (R&(-R)); 
		}
	}
	return ret;
}
 
int main (void)
{
	int m;
	while (scanf ("%d%d", &n, &m) != EOF) {
		memset (h, 0, sizeof (h));
		for (int i = 1; i <= n; ++i) {
			scanf ("%d", &a[i]);
			add (i, a[i]);
		}
		char op[2], b[10]; int x, y;
		while (m--) {
			scanf ("%s%d%d", op, &x, &y);
			gets (b);
			if (!strcmp (op, "U")) {
				a[x] = y; add (x, y);				
			} else {
				printf ("%d\n", query (x, y));
			}
		}
		
	}
	return 0;
 } 