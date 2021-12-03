#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <deque>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(NULL) {}
};

int minOperations(int n) {
    if (n == 0) return 0;
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += 2 * i + 1;
    }
    int medium = sum / n;
    int sq = 0;
    for (int i = 0; i < n; i++) {
        sq += abs(medium - 2 * i - 1);
    }
    return sq / 2;
}

int main() {
    cout << minOperations(3) << endl;
    cout << minOperations(6) << endl;
    return 0;
}