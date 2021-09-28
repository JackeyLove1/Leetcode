// Author: Jacky
// Time: 2021-09-27
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <bitset>
#include <cstring>
#include <queue>
#include <tuple>
#include <deque>

using namespace std;
using PII = pair<int, int>;
using ll = long long;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t; });
    cout << endl;
}

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

const int debug = 0;

inline vector<int> add(vector<int> &A, vector<int> &B) {
    int sz = max(A.size(), B.size());
    vector<int> C;
    int t = 0;
    for (int i = 0; i < sz; ++i) {
        int x = i < A.size() ? A[i] : 0;
        int y = i < B.size() ? B[i] : 0;
        int sum = x + y + t;
        C.push_back(sum % 10);
        t = sum / 10;
    }
    if (debug) {
        cout << "A: " << endl;
        print(A);
        cout << "B: " << endl;
        print(B);
    }
    if (t) C.push_back(t);
    reverse(C.begin(), C.end());
    return C;
}

int main() {
    fhj();
    string a, b;
    cin >> a >> b;
    vector<int> A, B;
    for (int i = a.size() - 1; i >= 0; --i) A.push_back(a[i] - '0');
    for (int i = b.size() - 1; i >= 0; --i) B.push_back(b[i] - '0');
    auto C = add(A, B);
    print(C);
    return 0;
}