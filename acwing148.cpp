#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <unordered_set>
#include <cstring>

using namespace std;

const int N = 100010;

int main() {
    int n;
    cin >> n;
    priority_queue<int, vector<int>, greater<>> heap;
    int sum = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        heap.push(x);
    }

    while (heap.size() > 1) {
        int a = heap.top();
        heap.pop();
        int b = heap.top();
        heap.pop();
        int c = a + b;
        sum += c;
        heap.push(c);
    }

    cout << sum << endl;
    return 0;
}