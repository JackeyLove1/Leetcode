#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>
#include <cstring>
#include <string>
#include <string_view>

using namespace std;
constexpr int INF = 0x3f3f3f3f;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

template<typename T>
inline void print(vector<T> &vec) {
    for_each(vec.begin(), vec.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

struct node {
    int x, y, color, weight;

    explicit node(int x_, int y_, int color_, int weight_) :
            x(x_), y(y_), color(color_), weight(weight_) {}

    bool operator<(const node &rhs) const {
        return weight > rhs.weight;
    }
};

priority_queue<node> q;
constexpr int dx[] = {0, 1, 0, -1, 1, 1, -1, -1, 0, 2, 0, -2};//12方向及魔法代价
constexpr int dy[] = {1, 0, -1, 0, 1, -1, 1, -1, 2, 0, -2, 0};
constexpr int dw[] = {0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2};
constexpr int N = 110;
int color[N][N], dis[N][N];
int n, m;

void bfs() {
    memset(dis, 0x3f, sizeof dis);
    dis[1][1] = 0;
    q.push(node{1, 1, color[1][1], 0});
    while (!q.empty()) {
        auto cur = q.top();
        q.pop();
        auto[curx, cury, curc, curw] = cur;
        // 满足更新条件再更新
        if (dis[curx][cury] < curw) continue;
        for (int i = 0; i < 12; ++i) {
            auto next_x = curx + dx[i];
            auto next_y = cury + dy[i];
            auto next_w = curw + dw[i];
            // 检查坐标和颜色是否满足条件
            if (next_x <= 0 || next_x > m || next_y <= 0 || next_y > m) continue;
            auto next_c = color[next_x][next_y];
            if (!next_c) continue; // 无色格子跳过
            if (next_c != curc) next_w++; // 不同颜色计算步数
            if (next_w < dis[next_x][next_y]) {
                dis[next_x][next_y] = next_w;
                q.emplace(next_x, next_y, next_c, next_w);
            }
        }
    }
}

class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        // string_view sv = s;
        int n = s.size();
        if (n > 12) return {};
        vector<string> res;
        auto check = [](string &s) -> bool {
            if (s.size() == 1 || (s.size() > 1 && s.size() <= 3 && s[0] != '0')) {
                auto anum = stoi(s);
                return anum <= 255;
            }
            return false;
        };

        for (int a = 0; a < 3; ++a) {
            auto astr = s.substr(0, a - 0 + 1);
            if (!check(astr)) continue;
            for (int b = a + 1; b < n; ++b) {
                auto bstr = s.substr(a + 1, b - a);
                if (!check(bstr)) continue;
                for (int c = b + 1; c < n; ++c) {
                    auto cstr = s.substr(b + 1, c - b);
                    if (!check(cstr)) continue;
                    auto dstr = s.substr(c + 1);
                    if (!check(dstr)) continue;
                    auto tmp = astr + "." + bstr + "." + cstr + "." + dstr;
                    res.emplace_back(tmp);
                }
            }
        }
        return res;
    }
};

int main() {
    string str = "25525511135";
    Solution s;
    auto vec = s.restoreIpAddresses(str);
    print(vec);
    auto vec2 = s.restoreIpAddresses("0000");
    print(vec2);
    auto vec3 = s.restoreIpAddresses("1111");
    print(vec3);
    auto vec4 = s.restoreIpAddresses("010010");
    print(vec4);
}