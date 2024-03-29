/*
给定一个 n 次多项式 F(x)=a0+a1x+a2x2+…+anxn。
以及一个 m 次多项式 G(x)=b0+b1x+b2x2+…+bmxm。
已知 H(x)=F(x)⋅G(x)=c0+c1x+c2x2+…+cn+mxn+m。
请你计算并输出 c0,c1,…,cn+m。

输入格式
第一行包含两个整数 n,m。
第二行包含 n+1 个整数 a0,a1,…,an。
第三行包含 m+1 个整数 b0,b1,…,bm。
输出格式
共一行，依次输出 c0,c1,…,cn+m。
*/
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

const int N = 300010;
const double PI = acos(-1);

int n, m;
struct Complex
{
    double x, y;
    Complex operator+ (const Complex& t) const
    {
        return {x + t.x, y + t.y};
    }
    Complex operator- (const Complex& t) const
    {
        return {x - t.x, y - t.y};
    }
    Complex operator* (const Complex& t) const
    {
        return {x * t.x - y * t.y, x * t.y + y * t.x};
    }
}a[N], b[N];
int rev[N], bit, tot;

void fft(Complex a[], int inv)
{
    for (int i = 0; i < tot; i ++ )
        if (i < rev[i])
            swap(a[i], a[rev[i]]);
    for (int mid = 1; mid < tot; mid <<= 1)
    {
        auto w1 = Complex({cos(PI / mid), inv * sin(PI / mid)});
        for (int i = 0; i < tot; i += mid * 2)
        {
            auto wk = Complex({1, 0});
            for (int j = 0; j < mid; j ++, wk = wk * w1)
            {
                auto x = a[i + j], y = wk * a[i + j + mid];
                a[i + j] = x + y, a[i + j + mid] = x - y;
            }
        }
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= n; i ++ ) scanf("%lf", &a[i].x);
    for (int i = 0; i <= m; i ++ ) scanf("%lf", &b[i].x);
    while ((1 << bit) < n + m + 1) bit ++;
    tot = 1 << bit;
    for (int i = 0; i < tot; i ++ )
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
    fft(a, 1), fft(b, 1);
    for (int i = 0; i < tot; i ++ ) a[i] = a[i] * b[i];
    fft(a, -1);
    for (int i = 0; i <= n + m; i ++ )
        printf("%d ", (int)(a[i].x / tot + 0.5));

    return 0;
}

/*
// 高精度乘法
#pragma GCC optimize(2)
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <numeric>
#include <cmath>

using namespace std;
using sll = __int128;
using ull = unsigned long long;
using ll = long long;
using PII = pair<int, int>;

static inline int read() {
    int x = 0, f = 0, ch;
    while (!isdigit(ch = getchar())) f |= ch == '-';
    while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    return f ? -x : x;
}

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 3e5 + 10;
const double PI = acos(-1);

int n, m;

struct Complex {
    double x, y;

    Complex operator+(const Complex &t) const {
        return {x + t.x, y + t.y};
    }

    Complex operator-(const Complex &t) const {
        return {x - t.x, y - t.y};
    }

    Complex operator*(const Complex &t) const {
        return {x * t.x - y * t.y, x * t.y + y * t.x};
    }
} a[N], b[N];

int c[N * 2];

int rev[N], bit, tot;

void fft(Complex a[], int inv) {
    for (int i = 0; i < tot; i++)
        if (i < rev[i])
            swap(a[i], a[rev[i]]);
    for (int mid = 1; mid < tot; mid <<= 1) {
        auto w1 = Complex({cos(PI / mid), inv * sin(PI / mid)});
        for (int i = 0; i < tot; i += mid * 2) {
            auto wk = Complex({1, 0});
            for (int j = 0; j < mid; j++, wk = wk * w1) {
                auto x = a[i + j], y = wk * a[i + j + mid];
                a[i + j] = x + y, a[i + j + mid] = x - y;
            }
        }
    }
}

void get_fft(Complex a[], Complex b[], int c[]) {
    while ((1 << bit) < n + m + 1) bit++;
    tot = 1 << bit;
    for (int i = 0; i < tot; i++)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
    fft(a, 1), fft(b, 1);
    for (int i = 0; i < tot; i++) a[i] = a[i] * b[i];
    fft(a, -1);
    for (int i = 0; i <= n + m; i++) {
        c[i] = static_cast<int>((a[i].x / tot + 0.5));
    }
}

char A[N], B[N];
int res[N];
int main() {
    scanf("%s", A);
    scanf("%s", B);
    n = strlen(A) - 1, m = strlen(B) - 1;
    for (int i = 0; i <= n; ++i) a[i].x = A[n - i] - '0';
    for (int i = 0; i <= m; ++i) b[i].x = B[m - i] - '0';
    get_fft(a, b, c);

    int k = 0;
    for (int i = 0, t = 0; i < tot || t; ++i){
        t += c[i];
        res[k++] = t % 10;
        t /= 10;
    }
    while (k > 1 && !res[k-1]) --k;
    for(int i = k - 1; i >= 0; --i) cout << res[i];
    return 0;
}
*/