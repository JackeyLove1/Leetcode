#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// plus one
// 高精度加法
void plusOne(vector<int> &digits) {
    int carry = 1;
    // 使用反向遍历，然后逐位加carry的操作
    for (auto it = digits.rbegin(); it != digits.rend(); it++) {
        if (carry == 0) break;
        *it = *it + carry;
        carry = *it / 10;
        *it = *it % 10;
    }
    if (carry > 0) digits.insert(digits.begin(), carry);
}

void print(vector<int> &digits) {
    for (auto digit : digits) {
        cout << digit << " ";
    }
    cout << endl;
}

// test function
int main() {
    vector<int> digits = {1, 2, 3, 4, 9};
    cout << "before plus one" << endl;
    print(digits);
    plusOne(digits);
    cout << "after  plus one" << endl;
    print(digits);
    return 0;
}