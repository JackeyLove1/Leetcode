#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <functional>

using namespace std;

// 深度优先搜索方法
void count(int amount, vector<int> &coins, int step, int &cnt) {
    if (amount < 0 || step >= coins.size())
        return;
    if (amount == 0) {
        cnt++;
        return;
    }
    for (int i = step; i < coins.size(); i++) {
        count(amount - coins[i], coins, i, cnt);
    }
}

int change(int amount, vector<int> &coins) {
    if(amount == 0) return 1;
    int cnt = 0;
    count(amount, coins, 0, cnt);
    return cnt;
}

int main() {
    vector<int> coins = {1, 2, 5};
    cout << change(5, coins) << endl;
    vector<int> coins2 = {3,5,7,8,9,10,11};
    cout << change(500, coins2) << endl;
}