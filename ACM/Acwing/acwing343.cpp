#include <unordered_map>
#include <unordered_set>
#include <map>
#include <iostream>
#include <sstream>
#include <utility>
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

inline int count(int state) {
    return __builtin_popcount(state);
}

constexpr int N = 33, INF = 0x3f3f3f3f;
int n, m, dist[N][N], ans[N];

void floyd() {
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
}

int main() {
    fhj();
    while (cin >> n >> m && n != 0 && m != 0) {
        memset(dist, 0x3f, sizeof dist);
        int flag = 0;
        for (int u = 1; u <= m; u++) {
            char a, c, b;
            cin >> a >> c >> b;
            int x = a - 'A' + 1, y = b - 'A' + 1;
            if (x == y) {
                printf("Inconsistency found after %d relations.\n", u);
                flag = 1;
                break;
            }
            dist[x][y] = 1;
            if (flag) continue;
            floyd();
            int anscnt = 0;
            for (int i = 1; i <= n; i++) {
                int cnt = 0, cnt1 = 0;
                for (int j = 1; j <= n; j++) {
                    if (i == j) continue;
                    if (dist[i][j] != INF && dist[j][i] != INF) {
                        printf("Inconsistency found after %d relations.\n", u);
                        flag = 1;
                        break;
                    }
                    if (dist[j][i] != INF) cnt++;
                    if (dist[i][j] != INF) cnt1++;
                }
                if (flag == 1) break;

                if (cnt + cnt1 == n - 1) ans[cnt + 1] = i, anscnt++;
            }
            if (anscnt == n && !flag) {
                printf("Sorted sequence determined after %d relations: ", u);
                for (int i = 1; i <= n; i++) cout << char(ans[i] + 'A' - 1);
                cout << "." << endl;
                flag = 1;
            }
        }
        if (flag == 0) cout << "Sorted sequence cannot be determined." << endl;
    }

    return 0;
}

