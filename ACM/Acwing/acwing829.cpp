#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include <queue>

using namespace std;

int main() {
    int m;
    ios::sync_with_stdio(false);
    cin >> m;
    string op;
    int val;
    deque<int>vec;
    while (m--) {
        cin >> op;
        if (op == "push") {
            cin >> val;
            vec.push_back(val);
        } else if (op == "pop") {
            vec.pop_front();
        } else if (op == "query") {
            cout << vec.front() << endl;
        } else {
            if (vec.empty())
                cout << "YES" << endl;
            else
                cout << "NO" << endl;
        }
    }

    return 0;
}