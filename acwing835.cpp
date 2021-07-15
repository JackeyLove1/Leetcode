#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <stack>

using namespace std;

int main() {
    int n;
    cin >> n;
    unordered_map<string, int> um;
    while (n--) {
        char op;
        string s;
        cin >> op >> s;
        if (op == 'I') {
            um[s]++;
        } else {
            cout << um[s] << endl;
        }
    }

    return 0;
}