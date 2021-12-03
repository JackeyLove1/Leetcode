// Author: Jacky
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <bitset>
#include <cstring>
#include <queue>
#include <tuple>
#include <deque>
#include <numeric>


using namespace std;
using PII = pair<int, int>;
using ll = long long;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

class Bank {
    int n;
    vector<long long> balance;
public:
    Bank(vector<long long> &balance) : balance(balance) {
        n = balance.size();
    }

    bool transfer(int account1, int account2, long long money) {
        if (account1 < 1 || account1 > n) return false;
        if (account2 < 1 || account2 > n) return false;

        account1--, account2--;

        if (balance[account1] >= money) {
            balance[account1] -= money;
            balance[account2] += money;
            return true;
        }
        return false;
    }

    bool deposit(int account, long long money) {
        if (account < 1 || account > n) return false;
        account--;
        balance[account] += money;
        return true;
    }

    bool withdraw(int account, long long money) {
        if (account < 1 || account > n) return false;
        account--;
        if (balance[account] < money)
            return false;
        balance[account] -= money;
        return true;
    }
};

/**
 * Your Bank object will be instantiated and called as such:
 * Bank* obj = new Bank(balance);
 * bool param_1 = obj->transfer(account1,account2,money);
 * bool param_2 = obj->deposit(account,money);
 * bool param_3 = obj->withdraw(account,money);
 */


int main() {
    vector<long long> nums = {10, 100, 20, 50, 30};
    auto s = Bank(nums);
    cout << s.withdraw(3, 10) << endl;
    cout << s.transfer(5, 1, 20) << endl;
}