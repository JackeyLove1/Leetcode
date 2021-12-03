#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <functional>

using namespace std;

inline void print(vector<int> &nums) {
    for (auto &num : nums) cout << num << " ";
    // cout << "end..." << endl;
}

string addBinary(string a, string b) {
    string c;
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    int n = a.size(), m = b.size();
    int i = 0, j = 0;
    int carry = 0;
    int x, y, z;
    while (i < a.size() || j < b.size()) {
        char ch;
        x = (i < a.size()) ? a[i] - '0' : 0;
        y = (j < b.size()) ? b[j] - '0' : 0;
        z = x + y + carry;
        if (z == 3) {
            ch = '1', carry = 1;
        } else if (z == 2) {
            ch = '0', carry = 1;
        } else if (z == 1) {
            ch = '1', carry = 0;
        } else {
            ch = '0', carry = 0;
        }
        c.push_back(ch);
        i++, j++;
    }
    if (carry) c.push_back('1');
    reverse(c.begin(), c.end());
    return c;
}

int main() {
    string a, b;
    while (cin >> a >> b) {
        auto c = addBinary(a, b);
        cout << c << endl;
    }
    return 0;
}