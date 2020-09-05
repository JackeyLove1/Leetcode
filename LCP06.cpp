#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int getNumbers(int n) {
    if (n == 0)
        return 0;
    if (n % 2 == 0)
        return n / 2;
    return int(n/2) + 1;
}

int minCount(vector<int> &coins) {
    int res = 0;
    for (auto coin : coins){
        res += getNumbers(coin);
    }
    return res;
}