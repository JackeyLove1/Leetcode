#include <unordered_map>
#include <map>
#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <string>

// #pragma GCC optimize(2)

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

const double e = exp(1.0);
double p[21];

int main() {
    fhj();
    double temp = 1.0;

    int t, n, i;
    for (i = 2; i <= 20; i++) {
        temp *= i;//求阶乘
        p[i] = round(temp / e) / temp;//round是求四舍五入的值错排公式
    }
    cin >> t;
    while (t--) {
        cin >> n;
        printf("%.2f%%\n", p[n] * 100.0);//乘100改成百分数

    }
    return 0;
}