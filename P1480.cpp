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

inline vector<int> div(vector<int> &A, int b) {
    vector<int> C;
    ll r = 0;
    for (int i = 0; i < A.size(); ++i) {
        r = r * 10 + A[i];
        C.push_back(r / b);
        r = r % b;

    }
    reverse(C.begin(), C.end());
    while (!C.empty() && C.back() == 0) C.pop_back();
    return C;
}

int main() {
    fhj();
    string a;
    int b;
    cin >> a >> b;
    vector<int> A;
    for (int i = 0; i < a.size(); ++i) A.push_back(a[i] - '0');
    auto C = div(A, b);
    reverse(C.begin(), C.end());
    print(C);
    return 0;
}