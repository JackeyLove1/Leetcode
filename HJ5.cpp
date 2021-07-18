#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;

int main() {
    string s;
    while (cin >> s) {
        int cnt = 0;
        s = s.substr(2);
        reverse(s.begin(), s.end());
        long long res = 0;
        for (char i : s) {
            int ch;
            if (i >= '0' && i <= '9') {
                ch = i - '0';
            } else {
                ch = i - 'A' + 10;
            }
            res += ch * int(pow(16, cnt));
            cnt++;
        }
        cout << res << endl;
    }
    return 0;
}