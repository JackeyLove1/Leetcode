#include <unordered_map>
#include <unordered_set>
#include <map>
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>
#include <queue>
#include <set>
#include <tuple>
#include <list>
#include <atomic>
#include <thread>

#include <cstring>
#include <cmath>
#include <cstdlib>
#include <iostream>

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

int n;
constexpr int N = 1010;

struct Node {
    int l, r;
    int h;

    explicit Node(int a, int b, int c) : l(a), r(b), h(c) {
        if (l > r) {
            swap(l, r);
        }
    }

    bool operator<(const Node &rhs) const {
        return l < rhs.l && r < rhs.r;
    }
};

vector<Node> datas;

// int edge[N][N];
int f[N];
int a, b, c;

int main() {
    fhj();
    int T;
    cin >> T;
    datas.reserve(N * 3);
    while (T--) {
        cin >> n;
        datas.clear();
        for (int i = 0; i < n; ++i) {
            cin >> a >> b >> c;
            datas.emplace_back(a, b, c);
            datas.emplace_back(a, c, b);
            datas.emplace_back(b, c, a);
        }
        sort(datas.begin(), datas.end());
        memset(f, 0, sizeof f);
        int res = 0;
        for(int i = 0; i < datas.size(); ++i){
            for(int j = 0; j < i; ++j){
                if (datas[j] < datas[i]){
                    f[i] = max(f[i], f[j] + 1);
                }
            }
            res = max(res, f[i]);
        }
        cout << res << endl;
    }
    return 0;
}