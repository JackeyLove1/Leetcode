#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <unordered_map>
#include <map>
#include <bitset>
#include <queue>
#include <deque>
#include <unordered_set>
#include <cmath>
#include <set>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

using ll = long long;

inline int cnt(int x) {
    return __builtin_popcount(x);
}


constexpr int N = 1e5 + 100;
int n, m;

struct node {
    int id, score;

    node(int _id, int _score) : id(_id), score(_score) {}

    bool operator<(const node &rhs) const {
        if (score == rhs.score) {
            return id < rhs.id;
        }
        return score > rhs.score;
    }
};

int main() {
    fhj();
    vector<node> nums;
    cin >> n >> m;
    int a, b;
    for (int i = 1; i <= n; ++i) {
        cin >> a >> b;
        nums.emplace_back(a, b);
    }
    sort(nums.begin(), nums.end());
    int k = ceil(m * 1.5);
    cout << nums[k].score << " " << k << endl;
    for (int i = 0; i <= min((int) nums.size() - 1, k - 1); ++i) {
        cout << nums[i].id << " " << nums[i].score << endl;
    }
    return 0;
}