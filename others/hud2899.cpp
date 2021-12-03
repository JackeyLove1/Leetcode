#include <iostream>
#include <algorithm>
#include <functional>
#include <cstring>
#include <vector>
#include <map>
#include <cmath>

using namespace std;

const double eps = 1e-8; // 终止温度
double y;

double func(double x) { // 计算函数值
    return 6 * pow(x, 7) + 8 * pow(x, 6) + 7 * pow(x, 3) + 5 * pow(x, 2) - y * x;
}

// 模拟退火算法
// 常用于解决函数极值问题，旅行商问题等
double solve() {
    double T = 100; // 初始温度
    double delta = 0.98; // 降温系数
    double x = 50.0; // x的初始值
    double now = func(x); // 计算初始值函数
    double ans = now; // 返回值
    while (T > eps) { // eps是终止温度
        int f[2] = {1, -1};
        // 按概率改变x，随T的降温而减少
        double newx = x + f[rand() % 2] * T;
        if (newx >= 0 && newx <= 100) {
            double next = func(newx);
            ans = min(ans, next);
            if (now - next > eps) {
                x = newx;
                now = next;
            } // 更新x
        }
        T *= delta;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    while (n--) {
        cin >> y;
        // cout << solve() << endl;
        printf("%.4f\n", solve());
    }
    return 0;
}