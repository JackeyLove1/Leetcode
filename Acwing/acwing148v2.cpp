#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <functional>
#include <climits>
#include <queue>

using namespace std;

int n, k;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    priority_queue<int, vector<int>, greater<>> heap;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> k;
        heap.push(k);
    }

    int sum = 0;
    while (heap.size() > 1) {
        int a = heap.top();
        heap.pop();
        int b = heap.top();
        heap.pop();
        int c = a + b;
        heap.push(c);
        sum += c;
    }
    cout << sum << endl;
    return 0;
}