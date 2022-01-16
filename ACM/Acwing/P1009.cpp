#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <climits>
#include <functional>

using namespace std;

constexpr int N = 50;
int n;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t; });
    cout << endl;
}

// a: 低位到高位
inline void multiply(vector<int> &a, int b) {
    int carry = 0;
    for (int i = 0; i < a.size(); i++) {
        int tmp = a[i] * b + carry;
        a[i] = tmp % 10;
        carry = tmp / 10;
    }
    if (carry) a.push_back(carry);
}

inline void add(vector<int> &a, vector<int> &b) {
    // 将b数组加到a数组上
    int carry = 0;
    vector<int> c;
    int sz = max(a.size(), b.size());
    for (int i = 0; i < sz; i++) {
        int x = i >= a.size() ? 0 : a[i];
        int y = i >= b.size() ? 0 : b[i];
        int tmp = x + y + carry;
        c.push_back(tmp % 10);
        carry = tmp >= 10 ? tmp / 10 : 0;
    }
    if (carry) c.push_back(carry);
    a = move(c);
}

int main() {
    cin >> n;
    vector<int> a = {1}, res = {0};
    while (n) {
        multiply(a, n);
        // cout <<"a: "; print(a);
        add(res, a);
        // cout <<"res: "; print(res);
        if (--n == 1) break;
    }
    reverse(res.begin(), res.end());
    print(res);
    return 0;
}