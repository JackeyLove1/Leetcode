#include <iostream>
#include <string>
#include <cmath>
#include <cassert>

using namespace std;

using ll = long long;

ll stoi(string &s) {
    int sz = s.size();
    reverse(s.begin(), s.end());
    int res = 0;
    for (int i = 0; i < sz; ++i) {
        if (s[i] == '0' || s[i] == '1') {
            res += (s[i] - '0') * pow(2, i);
        } else {
            cout << "input error: not 0 or 1" << endl;
            return -1;
        }
    }
    return res;
}

int main() {
    string s1 = "1", s2 = "2", s3 = "10", s4 = "0abc", s5 = "11111111";
    string s6 = "01";
    cout << stoi(s1) << " res: 1" << endl;
    cout << stoi(s2) << " res: -1" << endl;
    cout << stoi(s3) << " res: 2" << endl;
    cout << stoi(s4) << " res: -1" << endl;
    cout << stoi(s5) << " res: " << int(pow(2, s5.size())-1) << endl;
    cout << stoi(s6) << " res: 1" << endl;
    return 0;
}