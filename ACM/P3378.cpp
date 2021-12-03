#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
#include <unordered_map>
#include <bitset>
#include <cstring>
#include <queue>

using namespace std;

int n;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    priority_queue<int, vector<int>, greater<int>> heap;
    cin >> n;
    while (n--) {
        int op, x;
        cin >> op;
        if (op == 1) {
            cin >> x;
            heap.push(x);
        } else if (op == 2) {
            cout << heap.top() << endl;
        } else {
            heap.pop();
        }
    }
    return 0;
}