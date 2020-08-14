// 斐波那契
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long fib(int N) {
    vector<long> dp(N + 1, 0);
    dp[1] = dp[2] = 1;
    for (int i = 3; i <= N; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[N];
}

int main() {
    cout << fib(10) << endl;
    return 0;
}