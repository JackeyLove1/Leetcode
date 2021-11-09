#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <unordered_map>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

using ll = long long;

inline int cnt(int x) {
    return __builtin_popcount(x);
}

constexpr int LEN = 1e5+10;

struct BIGNUM {
    static const int BIT = 9;
    static const int MOD = 1000000000;//1eBIT
    bool flag;//0 for 0 or positive, 1 for negative
    ll s[LEN];

    BIGNUM() {
        flag = 0;
        memset(s, 0, sizeof(s));
        s[0] = 1;
    }

    void init() {//数组清零
        memset(s, 0, sizeof(s));
    }

    void print() {//打印
        BIGNUM a = *this;
        if (a.flag)
            printf("-");
        printf("%lld", a.s[a.s[0]]);
        for (int i = a.s[0] - 1; i > 0; i--) {
            printf("%09lld", a.s[i]);
        }
        printf("\n");
    }

    BIGNUM operator=(const char *num) {
        if (num[0] == '-') {
            flag = 1;
            num++;
        } else if (num[0] == '+') {
            flag = 0;
            num++;
        }
        int l = strlen(num);
        s[0] = 0;
        for (int i = l - 1; i > -9; i -= 9) {
            int temp = 0;
            for (int j = i - 8; j <= i; j++) {
                if (j < 0)
                    continue;
                else {
                    temp = (temp << 1) + (temp << 3);
                    temp += num[j] ^ 48;
                }
            }
            s[++s[0]] = temp;
        }
        while (!s[s[0]] && s[0] > 1) s[0]--;
        return *this;
    }

    BIGNUM operator=(const int num) {
        char a[LEN];
        sprintf(a, "%d", num);
        *this = a;
        return *this;
    }

    BIGNUM(int num) { *this = num; }

    BIGNUM(const char *num) { *this = num; }

    BIGNUM(string &str) { *this = str.c_str(); }

    bool operator<(const BIGNUM &a) {
        if (flag > a.flag) return 1;
        else if (flag < a.flag) return 0;
        else {
            if ((s[0] < a.s[0] && (!flag)) || (s[0] > a.s[0] && flag)) return 1;
            else if (s[0] != a.s[0]) return 0;
            else {
                for (int i = s[0]; i > 0; i--) {
                    if (s[i] < a.s[i]) {
                        if (flag) return 0;
                        else return 1;
                    } else if (s[i] > a.s[i]) {
                        if (flag) return 1;
                        else return 0;
                    }
                }
                return 0;
            }
        }
    }

    bool operator>(const BIGNUM &a) {
        if (flag > a.flag) return 0;
        else if (flag < a.flag) return 1;
        else {
            if ((s[0] > a.s[0] && (!flag)) || (s[0] < a.s[0] && flag)) return 1;
            else if (s[0] != a.s[0]) {
                return 0;
            } else {
                for (int i = s[0]; i > 0; i--) {
                    if (s[i] > a.s[i]) {
                        if (flag) return 0;
                        else return 1;
                    } else if (s[i] < a.s[i]) {
                        if (flag) return 1;
                        else return 0;
                    }
                }
                return 0;
            }
        }
    }

    bool operator==(const BIGNUM &a) {
        if (flag != a.flag) return 0;
        else {
            if (s[0] != a.s[0]) return 0;
            else {
                for (int i = s[0]; i > 0; i--) {
                    if (s[i] != a.s[i]) return 0;
                }
                return 1;
            }
        }
    }

    bool operator>=(const BIGNUM &a) {
        if (*this > a || *this == a) return 1;
        return 0;
    }

    bool operator<=(const BIGNUM &a) {
        return (*this == a) || (*this < a);
    }

    int cmp_abs(const BIGNUM &a) {//1 for this > a, 0 for this == a, -1 for this < a
        if (s[0] > a.s[0])
            return 1;
        else if (s[0] < a.s[0])
            return -1;
        else {
            for (int i = s[0]; i > 0; i--) {
                if (s[i] > a.s[i])
                    return 1;
                else if (s[i] < a.s[i])
                    return -1;
            }
        }
        return 0;
    }

    BIGNUM operator+(const BIGNUM &B) {
        BIGNUM c, a = *this, b = B;
        if (!(a.flag || b.flag) || (a.flag && b.flag)) {
            c.flag = a.flag;
            int x = 0;
            c.s[0] = max(a.s[0], b.s[0]) + 1;
            for (int i = 1; i <= c.s[0]; i++) {
                c.s[i] = a.s[i] + b.s[i] + x;
                x = c.s[i] / MOD;
                c.s[i] %= MOD;
            }
        } else if (a.flag) {// a < 0
            if (a.cmp_abs(b) == 1) {//|a| > |b|, |ans| = |a| - |b|
                c.flag = 1;
                c.s[0] = max(a.s[0], b.s[0]) + 1;
                for (int i = 1; i <= c.s[0]; i++) {
                    c.s[i] = a.s[i] - b.s[i];
                    if (c.s[i] < 0) {
                        c.s[i] += MOD;
                        a.s[i + 1]--;
                    }
                }
            } else {//|a| <= |b|, |ans| = |b| - |a|
                c.flag = 0;
                c.s[0] = max(a.s[0], b.s[0]) + 1;
                for (int i = 1; i <= c.s[0]; i++) {
                    c.s[i] = b.s[i] - a.s[i];
                    if (c.s[i] < 0) {
                        c.s[i] += MOD;
                        b.s[i + 1]--;
                    }
                }
            }
        } else {// b < 0
            if (b.cmp_abs(a) == 1) {// |b| > |a|, |ans| = |b| - |a|
                c.flag = 1;
                c.s[0] = max(a.s[0], b.s[0]) + 1;
                for (int i = 1; i <= c.s[0]; i++) {
                    c.s[i] = b.s[i] - a.s[i];
                    if (c.s[i] < 0) {
                        c.s[i] += MOD;
                        b.s[i + 1]--;
                    }
                }
            } else {//|b| <= |a|, |ans| = |a| - |b|
                c.flag = 0;
                c.s[0] = max(a.s[0], b.s[0]) + 1;
                for (int i = 1; i <= c.s[0]; i++) {
                    c.s[i] = a.s[i] - b.s[i];
                    if (c.s[i] < 0) {
                        c.s[i] += MOD;
                        a.s[i + 1]--;
                    }
                }
            }
        }
        while (c.s[c.s[0]] == 0 && c.s[0] > 1) c.s[0]--;
        return c;
    }

    BIGNUM operator+(int num) {
        BIGNUM b = num, a = *this, c;
        c = a + b;
        return c;
    }

    BIGNUM operator+=(const BIGNUM &a) {
        *this = *this + a;
        return *this;
    }

    BIGNUM operator-(const BIGNUM &B) {
        BIGNUM c, a = *this, b = B;
        if ((!a.flag) && (!b.flag)) {
            if (a >= b) {
                c.flag = 0;
                c.s[0] = max(a.s[0], b.s[0]) + 1;
                for (int i = 1; i <= c.s[0]; i++) {
                    c.s[i] = a.s[i] - b.s[i];
                    if (c.s[i] < 0) {
                        c.s[i] += MOD;
                        a.s[i + 1]--;
                    }
                }
            } else {
                c.flag = 1;
                c.s[0] = max(a.s[0], b.s[0]) + 1;
                for (int i = 1; i <= c.s[0]; i++) {
                    c.s[i] = b.s[i] - a.s[i];
                    if (c.s[i] < 0) {
                        c.s[i] += MOD;
                        b.s[i + 1]--;
                    }
                }
            }
        } else {
            b.flag = !b.flag;
            c = a + b;
        }
        while (c.s[c.s[0]] == 0 && c.s[0] > 1) c.s[0]--;
        return c;
    }

    BIGNUM operator-(int num) {
        BIGNUM b = num, a = *this;
        BIGNUM c = a - b;
        return c;
    }

    BIGNUM operator-=(const BIGNUM &a) {
        *this = *this - a;
        return *this;
    }

    BIGNUM operator*(const BIGNUM &B) {
        BIGNUM c, a = *this, b = B;
        c.init();
        if (!(a.flag || b.flag) || (a.flag && b.flag))
            c.flag = 0;
        else {
            if ((a.s[0] == 1 && a.s[1] == 0) || (b.s[0] == 1 && b.s[1] == 0)) c = 0;
            else c.flag = 1;
        }
        c.s[0] = a.s[0] + b.s[0];
        for (int i = 1; i <= a.s[0]; i++) {
            int x = 0;
            for (int j = 1; j <= b.s[0]; j++) {
                c.s[i + j - 1] += a.s[i] * b.s[j] + x;
                x = c.s[i + j - 1] / MOD;
                c.s[i + j - 1] %= MOD;
            }
            c.s[i + b.s[0]] = x;
        }
        while (c.s[c.s[0]] > 0) c.s[0]++;
        while (c.s[c.s[0]] == 0 && c.s[0] > 1) c.s[0]--;
        return c;
    }

    BIGNUM operator*(int num) {
        BIGNUM b = num, a = *this;
        BIGNUM c = a * b;
        return c;
    }

    BIGNUM operator*=(const BIGNUM &a) {
        *this = *this * a;
        return *this;
    }

    BIGNUM operator<<(const int &a) {
        for (int i = 0; i < a; i++) {
            s[0]++;
            for (int j = s[0]; j > 0; j--) {
                s[j] <<= 1;
            }
            for (int j = 1; j < s[0]; j++) {
                if (s[j] >= MOD) {
                    s[j] -= MOD;
                    s[j + 1]++;
                }
            }
            while (s[s[0]] == 0 && s[0] > 1) s[0]--;
        }
        return *this;
    }

    BIGNUM operator<<=(const int &a) {
        *this = *this << a;
        return *this;
    }

    BIGNUM operator>>(const int &a) {
        for (int i = 0; i < a; i++) {
            for (int j = s[0]; j > 0; j--) {
                if ((s[j] & 1) && j != 1) s[j - 1] += MOD;
                s[j] >>= 1;
            }
        }
        while (s[s[0]] == 0 && s[0] > 1) s[0]--;
        return *this;
    }

    BIGNUM operator>>=(const int &a) {
        *this = *this >> a;
        return *this;
    }

    BIGNUM operator/(const BIGNUM &c) {
        BIGNUM a = *this, b = c, temp, ans;
        ans.init();
        temp.init();
        ans = 0;
        temp = 1;
        bool sign;
        if (!(a.flag || b.flag) || (a.flag && b.flag) || cmp_abs(c) == -1) sign = 0;
        else sign = 1;
        a.flag = b.flag = 0;
        while (a >= b) {
            b <<= 1;
            temp <<= 1;
        }
        while (temp.s[0] > 1 || temp.s[1]) {
            if (a >= b) {
                a -= b;
                ans += temp;
            }
            b >>= 1;
            temp >>= 1;
        }
        while (!ans.s[ans.s[0]] && ans.s[0] > 1) ans.s[0]--;
        ans.flag = sign;
        return ans;
    }

    BIGNUM operator/(int num) {
        BIGNUM b = num, a = *this;
        BIGNUM c = a / b;
        return c;
    }

    BIGNUM operator/=(const BIGNUM &a) {
        *this = *this / a;
        return *this;
    }

    BIGNUM operator%(const BIGNUM &a) {
        BIGNUM c = *this / a, d = c * a;
        return *this - d;
    }

    BIGNUM operator%=(const BIGNUM &a) {
        *this = *this % a;
        return *this;
    }
};

ostream &operator<<(ostream &out, const BIGNUM &a) {
    if (a.flag) putchar('-');
    printf("%lld", a.s[a.s[0]]);
    for (int i = a.s[0] - 1; i >= 1; i--)
        printf("%09lld", a.s[i]);
    return out;
}

istream &operator>>(istream &in, BIGNUM &a) {
    char str[LEN];
    in >> str;
    a = str;
    return in;
}

int main() {
    fhj();
    string a, b;
    cin >> a >> b;
    BIGNUM anum = a, bnum = b;
    auto cnum = anum + bnum;
    cnum.print();
    return 0;
}