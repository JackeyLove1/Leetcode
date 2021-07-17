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

int n;

struct Range {
    int l, r;

//    bool operator<(const Range &W) const {
//        return l < W.l;
//    }
} range[N];

int main() {
    int st, ed;
    scanf("%d%d", &st, &ed);
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        range[i] = {l, r};
    }

    sort(range, range + n, [](const Range& r1, const Range& r2){
        return r1.l < r2.l;
    });

    int res = 0;
    bool success = false;
    for (int i = 0; i < n; i++) {
        int j = i, r = -2e9;
        while (j < n && range[j].l <= st) {
            r = max(r, range[j].r);
            j++;
        }

        if (r < st) {
            res = -1;
            break;
        }

        res++;
        if (r >= ed) {
            success = true;
            break;
        }

        st = r;
        i = j - 1;
    }

    if (!success) res = -1;
    printf("%d\n", res);

    return 0;
}
