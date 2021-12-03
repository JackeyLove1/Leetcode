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

inline vector<int> mul(vector<int> &A, int b) {
    vector<int> C;
    for (int i = 0, t = 0; i < A.size() || t != 0; ++i) {
        if (i < A.size()) t += A[i] * b;
        C.push_back(t % 10);
        t /= 10;
    }
    if (debug) {
        print(A);
        cout << "b: " << b << endl;
        print(C);
    }
    while (C.size() > 1 && C.back() == 0) C.pop_back();
    return C;
}

int main() {
    fhj();
    int T;
    cin >> T;
    vector<int> A;
    while (T--) {
        int a, b;
        cin >> a >> b;
        A.clear();
        A.push_back(1);
        while (a > 1) {
            A = mul(A, a);
            --a;
        }
        int cnt = 0;
        for (int i = 0; i < A.size(); ++i) {
            if (A[i] == b)++cnt;
        }
        cout << cnt << endl;
    }
    return 0;
}