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

constexpr int N = 300010;
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
// tot代表最高位
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

int main() {
    fhj();
    cin >> n >> m;
    for (int i = 0; i <= n; ++i) cin >> a[i].x;
    for (int i = 0; i <= m; ++i) cin >> b[i].x;
    get_fft(a, b, c);
    for (int i = 0; i <= n + m; ++i) {
        cout << c[i] << " ";
    }
    return 0;
}