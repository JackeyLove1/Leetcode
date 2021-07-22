#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <queue>
#include <set>
#include <stack>

using namespace std;

int smallestDifference(vector<int> &a, vector<int> &b) {
    using ll = long long;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    int i = 0, j = 0;
    ll res = abs(a[i] - b[j]);
    while (i < a.size() && j < b.size()) {
        res = min(res, ll(abs(ll(a[i]) - ll(b[j]))));
        if (a[i] < b[j]) {
            i++;
        } else {
            j++;
        }
    }
    while (i < a.size()) res = min(res, ll(abs(ll(a[i++]) - ll(b.back()))));
    while (j < b.size()) res = min(res, ll(abs(ll(a.back()) - ll(b[j++]))));
    return res;
}