#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <queue>
#include <set>
#include <stack>

using namespace std;

string multiply(string num1, string num2) {
    if (num1.empty() || num2.empty()) return "0";
    reverse(num1.begin(), num1.end());
    reverse(num2.begin(), num2.end());
    string res(num1.size() + num2.size() + 1, '0');
    for (int i = 0; i < num1.size(); i++) {
        int d1 = num1[i] - '0';
        int carry = 0;
        for (int j = 0; j < num2.size(); j++) {
            int d2 = num2[j] - '0';
            int exist = res[i + j] - '0';
            res[i + j] = (d1 + d2 + carry + exist) % 10 + '0';
            carry = (d1 + d2 + carry + exist) / 10;
        }
        if (carry) {
            res[i + num2.size()] = carry + '0';
        }
    }
    while (!res.empty() && res.back() == '0') {
        res.pop_back();
    }
    if (res.empty()) return "0";
    reverse(res.begin(), res.end());
    return res;
}

int main() {
    cout << multiply("123", "456") << " res: 56088" << endl;
}