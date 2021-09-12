#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
#include <unordered_map>
#include <bitset>
#include <cstring>
#include <queue>
#include <tuple>

using namespace std;

constexpr int N = 1e3 + 100;
int n;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    vector<string> strs;
    string str;
    for (int i = 1; i <= n; ++i) {
        cin >> str;
        strs.emplace_back(str);
    }
    sort(strs.begin(), strs.end(), [](const string &a, const string &b) {
        return stoi(a + b) > stoi(b + a);
    });
    str.clear();
    for (auto &&s : strs) {
        str += s;
    }
    cout << str << endl;
    return 0;
}