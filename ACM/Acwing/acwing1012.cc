#pragma GCC optimize(2)

#include <bits/stdc++.h>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

template<typename T>
inline T read() {
    T ans = 0;
    char c = getchar();
    while (!isdigit(c)) c = getchar();
    while (isdigit(c)) ans = ans * 10 + c - '0', c = getchar();
    return ans;
}

using ll = long long;
#define rint read<int>()
#define rll read<ll>()
constexpr int N = 5500;

struct Node {
    int A, B;

    explicit Node(int A_, int B_) : A(A_), B(B_) {}

    bool operator<(const Node &rhs) const {
        return A < rhs.A;
    }
};

int f[N];

int main() {
    int n = rint;
    vector<Node> nums;
    nums.reserve(n);
    for (int i = 0; i < n; ++i) {
        int a = rint, b = rint;
        nums.emplace_back(a, b);
    }
    sort(nums.begin(), nums.end());
    int res = 0;
    for (int i = 0; i < n; ++i) {
        f[i] = 1;
        for (int j = 0; j < i; ++j) {
            if (nums[i].B > nums[j].B) {
                f[i] = std::max(f[i], f[j] + 1);
            }
        }
        res = std::max(res, f[i]);
    }
    cout << res << endl;
    return 0;
}