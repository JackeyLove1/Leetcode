// 堆排序

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
    int n, m, t;
    ios::sync_with_stdio(false);
    cin >> n >> m;
    priority_queue<int, vector<int>, greater<>> pq;
    for (int i = 0; i < n; i++) {
        cin >> t;
        pq.push(t);
    }
    for (int i = 0; i < m; i++) {
        cout << pq.top() << " ";
        pq.pop();
    }

    return 0;
}