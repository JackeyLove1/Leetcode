#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <unordered_set>

using namespace std;

int main() {
    int n;
    ios::sync_with_stdio(false);
    cin >> n;
    string s;
    unordered_set<int> us;
    int x;
    while (n--) {
        cin >> s >> x;
        if (s == "I") {
            us.insert(x);
        } else {
            if (us.count(x)) {
                cout << "Yes" << endl;
            } else {
                cout << "No" << endl;
            }
        }
    }
    return 0;
}