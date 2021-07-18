#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;

inline void doStr(string s) {
    if (s.empty()) {
        return;
    } else if (s.size() < 8) {
        for (int i = s.size(); i < 8; i++) {
            s.push_back('0');
        }
        cout << s << endl;
    } else if (s.size() == 8) {
        cout << s << endl;
    } else {
        cout << s.substr(0, 8) << endl;
        s = s.substr(8, s.size() - 8);
        doStr(s);
    }
}

int main() {
    string s;
    while (cin >> s) {
        doStr(s);
    }
    return 0;
}