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
// using sll = __int128;
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

inline int popcount(int x) {
    return __builtin_popcount(x);
}

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

constexpr int N = 330;

class scores {
public:
    int idx;
    int a, b, c;
    int sum_;

    explicit scores(int idx_, int a_, int b_, int c_)
            : idx(idx_), a(a_), b(b_), c(c_), sum_(a + b + c) {};

    bool operator<(const scores &rhs) const {
        if (sum_ != rhs.sum_) {
            return sum_ > rhs.sum_;
        } else if (a != rhs.a) {
            return a > rhs.a;
        } else {
            return true;
        }
    }
};

int main() {
    fhj();
    int n;
    cin >> n;
    vector<scores> students;
    students.reserve(n);
    for (int i = 1; i <= n; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        students.emplace_back(i, a, b, c);
    }
    sort(students.begin(), students.end());
    int cnt = 0;
    for (const auto &s: students) {
        cout << s.idx << " " << s.sum_ << endl;
        if (++cnt >= 5){
            break;
        }
    }
    return 0;
}