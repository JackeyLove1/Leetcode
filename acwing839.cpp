#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <stack>

using namespace std;

const int N = 1e6 + 100;

int main() {
    ios::sync_with_stdio(false);
    vector<int> v, vtmp;
    priority_queue<int, vector<int>, greater<>> pq;
    int n;
    cin >> n;
    string op;
    int k, x;
    while (n--) {
        cin >> op;
        if (op == "I") {
            cin >> x;
            pq.push(x);
            v.push_back(x);
        } else if (op == "PM") {
            cout << pq.top() << endl;
        } else if (op == "DM") {
            pq.pop();
        } else if (op == "D") {
            cin >> k;
            int tmp = v[k];
            vtmp.clear();
            while (pq.top() != tmp) {
                vtmp.push_back(pq.top());
                pq.pop();
            }
            pq.pop();
            for (auto &num : vtmp) pq.push(num);
        } else {
            cin >> k >> x;
            int tmp = v[k];
            vtmp.clear();
            while (pq.top() != tmp) {
                vtmp.push_back(pq.top());
                pq.pop();
            }
            pq.pop();
            pq.push(x);
            v[k] = x;
            for (auto &num : vtmp) pq.push(num);
        }
    }
    return 0;
}