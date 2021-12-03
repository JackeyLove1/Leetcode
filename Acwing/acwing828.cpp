#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <unordered_map>

using namespace std;

int main() {
    int m;
    ios::sync_with_stdio(false);
    cin >> m;
    string op;
    int val;
    vector<int> vec;
    while (m--) {
        cin >> op;
        if (op == "push") {
            cin >> val;
            vec.push_back(val);
        } else if (op == "pop") {
            vec.pop_back();
        } else if (op == "query") {
            cout << vec.back() << endl;
        } else {
            if (vec.empty())
                cout << "YES" << endl;
            else
                cout << "NO" << endl;
        }
    }

    return 0;
}