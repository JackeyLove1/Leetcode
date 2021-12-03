#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <unordered_set>

using namespace std;

int n, m;
int max_number = 0, max_index = -1;
constexpr int N = 1e5 + 100;
int father[N], cnt[N];

inline void init() {
    for (int i = 1; i <= n; i++) {
        father[i] = i;
        cnt[i] = 1;
    }
}

inline int find(int x) {
    if (father[x] != x) return father[x] = find(father[x]);
    return x;
}

// a < b
inline void merge(int a, int b) {
    int pa = find(a), pb = find(b);
    // cout << "a: " << a << " pa:" << pa << " b: " << b << " pb:" << pb << endl;
    if (pa == pb) {
        cout << max_number - cnt[pa] << endl;
        return;
    }
    if (pb > pa) {
        father[pa] = pb;
        cnt[pb] += cnt[pa];
        cnt[pa] = 0;
        if (max_number < cnt[pb]) {
            max_number = cnt[pb];
            max_index = pb;
        }
        // cout << "a: " << find(a) << " b:" << find(b) << endl;
    } else {
        father[pb] = pa;
        cnt[pa] += cnt[pb];
        cnt[pb] = 0;
        if (max_number < cnt[pa]) {
            max_number = cnt[pa];
            max_index = pa;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    init();
    while (m--) {
        int a, b;
        cin >> a >> b;
        merge(a, b);
    }
    for (int i = 1; i <= n; i++) {
        cout << find(i) << " ";
    }
    return 0;
}