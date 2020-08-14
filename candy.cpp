#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int candy(vector<int> &ratings) {
    int n = ratings.size();
    if (n == 0) return 0;
    if (n == 1) return 1;
    vector<int> candys(n, 1);
    // 从左到右扫描
    for (int i = 1; i < n; i++) {
        if (ratings[i] > ratings[i - 1])
            candys[i] = max(candys[i] + 1, candys[i - 1] + 1);
    }

    // 从右到左扫描
    for (int i = n - 2; i >= 0; i--) {
        if (ratings[i] > ratings[i + 1] && candys[i] <= candys[i + 1])
            candys[i] = max(candys[i] + 1, candys[i + 1] + 1);
    }

    // 计算和
    int sum = 0;
    for (auto c : candys) {
        sum += c;
    }
    return sum;
}

int main() {
    vector<int> ratings = {1, 0, 2};
    cout << candy(ratings) << endl;
    vector<int> ratings1 = {1, 2, 2};
    cout << candy(ratings1) << endl;
    vector<int> ratings2 = {1, 2, 87, 87, 87, 2, 1};
    cout << candy(ratings2) << endl;
    return 0;
}