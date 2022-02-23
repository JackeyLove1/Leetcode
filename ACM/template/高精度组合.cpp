#include <unordered_map>
#include <map>
#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <queue>
#include <sstream>
#include <numeric>

// #pragma GCC optimize(2)

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

template<typename T>
static inline void print(const vector<T> &nums) {
    if (nums.empty()) {
        cout << " empty !" << endl;
        return;
    }
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}


const int N = 1e4 + 10;

struct bign {
    int len, s[N];

    bign() {
        memset(s, 0, sizeof(s));
        len = 1;
    }

    bign(int num) { *this = num; }

    bign(char *num) { *this = num; }

    bign operator=(int num) {
        char c[N];
        sprintf(c, "%d", num);
        *this = c;
        return *this;
    }

    bign operator=(const char *num) {
        len = strlen(num);
        for (int i = 0; i < len; i++) s[i] = num[len - 1 - i] - '0';
        return *this;
    }

    string str() {
        string res = "";
        for (int i = 0; i < len; i++) res = (char) (s[i] + '0') + res;
        return res;
    }

    void clean() {
        while (len > 1 && !s[len - 1]) len--;
    }

    bign operator+(const bign &b) {
        bign c;
        c.len = 0;
        for (int i = 0, g = 0; g || i < len || i < b.len; i++) {
            int x = g;
            if (i < len) x += s[i];
            if (i < b.len) x += b.s[i];
            c.s[c.len++] = x % 10;
            g = x / 10;
        }
        return c;
    }

    bign operator-(const bign &b) {
        bign c;
        c.len = 0;
        int x;
        for (int i = 0, g = 0; i < len; i++) {
            x = s[i] - g;
            if (i < b.len) x -= b.s[i];
            if (x >= 0) g = 0;
            else {
                x += 10;
                g = 1;
            };
            c.s[c.len++] = x;
        }
        c.clean();
        return c;
    }

    bign operator*(const bign &b) {
        bign c;
        c.len = len + b.len;
        for (int i = 0; i < len; i++) for (int j = 0; j < b.len; j++) c.s[i + j] += s[i] * b.s[j];
        for (int i = 0; i < c.len - 1; i++) {
            c.s[i + 1] += c.s[i] / 10;
            c.s[i] %= 10;
        }
        c.clean();
        return c;
    }

    bool operator<(const bign &b) {
        if (len != b.len) return len < b.len;
        for (int i = len - 1; i >= 0; i--)
            if (s[i] != b.s[i]) return s[i] < b.s[i];
        return false;
    }

    bign operator+=(const bign &b) {
        *this = *this + b;
        return *this;
    }

    bign operator-=(const bign &b) {
        *this = *this - b;
        return *this;
    }
};

istream &operator>>(istream &in, bign &x) {
    string s;
    in >> s;
    x = s.c_str();
    return in;
}

ostream &operator<<(ostream &out, bign &x) {
    out << x.str();
    return out;
}

const int M = 10010;

int primes[M], cnt;
int sum[M];
bool st[M];


void get_primes(int n) {
    for (int i = 2; i <= n; i++) {
        if (!st[i]) primes[cnt++] = i;
        for (int j = 0; primes[j] <= n / i; j++) {
            st[primes[j] * i] = true;
            if (i % primes[j] == 0) break;
        }
    }
}


int get(int n, int p) {
    int res = 0;
    while (n) {
        res += n / p;
        n /= p;
    }
    return res;
}


bign cal(int a, int b) {
    memset(primes, 0, sizeof primes);
    cnt = 0;
    get_primes(a);

    for (int i = 0; i < cnt; i++) {
        int p = primes[i];
        sum[i] = get(a, p) - get(a - b, p) - get(b, p);
    }

    bign res = 1;

    for (int i = 0; i < cnt; i++)
        for (int j = 0; j < sum[i]; j++)
            res = res * primes[i];
    return res;
}

int main() {
    int n, m;
    cin >> n >> m;
    auto res1 = cal(m + n, n);
    auto res2 = cal(m + n, m - 1);
    auto res3 = res1 - res2;
    cout << res3 << endl;
    return 0;
}
