#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

using ll = long long;
using PII = pair<int, int>;
const int N = 1e5 + 10;
int n, m;
vector<int> x;
vector<PII> a;
vector<int> b;  // a<idx,cnt>垃圾 b<idx>居民

int find1(int c)  // <= c
{
    int l = 0, r = a.size() - 1;
    while (l < r) {
        int mid = l + r + 1 >> 1;
        if (a[mid].first <= c) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }
    return l;
}

int find2(int c) // >= c
{
    int l = 0, r = a.size() - 1;
    while (l < r) {
        int mid = l + r >> 1;
        if (a[mid].first >= c) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    return l;
}

int main() {
    fhj();
    cin >> n >> m;
    int k = n + m;

    for (int i = 0; i < k; ++i) {
        int c;
        scanf("%d", &c);
        x.emplace_back(c);
    }

    for (int i = 0; i < k; ++i) {
        int c;
        scanf("%d", &c);
        if (c) a.push_back({x[i], 0});
        else b.emplace_back(x[i]);
    }

    sort(a.begin(), a.end());
    //sort(b.begin(), b.end());


    for (int i = 0; i < b.size(); ++i) {
        int c = b[i];
        int x1 = find1(c), x2 = find2(c);
        if (x1 == x2) a[x1].second += 1;
        else {
            if (abs(c - a[x1].first) <= abs(c - a[x2].first)) a[x1].second += 1;
            else a[x2].second += 1;
        }

    }

    for (int i = 0; i < a.size(); ++i)
        printf("%d ", a[i].second);

    return 0;
}

