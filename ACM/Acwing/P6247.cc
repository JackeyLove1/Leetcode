#include <bits/stdc++.h>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 1e5 + 100;

template<typename T>
inline T pow(T t) {
    return t * t;
}

struct Node {
    double x, y;

    bool operator<(const Node &rhs) const {
        return x != rhs.x ? x < rhs.x : y < rhs.y;
    }
} p[N];

int n, m;
const int range = 20;

int main() {
    fhj();
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> p[i].x >> p[i].y;
    }
    sort(p, p + n);
    double minv = 1e9 + 100.0, maxv = 0.0;
    auto dis = [](const Node &lhs, const Node &rhs) -> double {
        return std::sqrt(pow(lhs.x - rhs.x) + pow(lhs.y - rhs.y));
    };
    for (int i = 0; i < n; ++i) {
        for (int j = 1; j <= range && i + j < n; ++j) {
            minv = std::min(minv, dis(p[i], p[i + j]));
        }
        for (int j = 1; j <= range && i < n - j; ++j) {
            maxv = std::max(maxv, dis(p[i], p[n - j]));
        }
    }
    printf("%.2f %.2f\n", minv, maxv);
    return 0;
}