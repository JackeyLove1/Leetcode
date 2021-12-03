#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <queue>
#include <cstring>
#include <tuple>


using namespace std;

inline void print(vector<int> &nums) {
    for_each(nums.begin(), nums.end(), [](int x) { cout << x << " "; });
    cout << endl;
}

class Solution {
public:
    // 使用模拟 + 最小堆
    using PII = pair<int, int>;
    using LL = long long;

    struct task {
        int  start, duration, index;

        friend ostream &operator<<(ostream &os, const task &t)  {
            os << "index: " << t.index << " st: " << t.start << " duration: " << t.duration << endl;
            return os;
        }
    };

    struct cmp {
        bool operator () (const task &t1, const task &t2) {
            if (t1.duration == t2.duration) return t1.start > t2.start;
            return t1.duration > t2.duration;
        }
    };

    vector<int> getOrder(vector<vector<int>> &tasks) {
        int n = tasks.size();
        vector<int> res(n, -1);
        vector<task> works;
        works.reserve(n);
        for (int i = 0; i < n; i++) {
            works.push_back({tasks[i][0], tasks[i][1], i});
        }
        sort(works.begin(), works.end(), [](const task &t1, const task &t2) {
            if (t1.start == t2.start) return t1.duration < t2.duration;
            return t1.start < t2.start;
        });
        // for_each(works.begin(), works.end(), [](const task &t) { cout << t << endl; });
        priority_queue<task, vector<task>, cmp> pq; // duration, start
        LL ts = 1;
        for (int j = 0, idx = 0; idx < n;) {
            while (j < n && works[j].start <= ts) pq.push(works[j]), j++;
            if (pq.empty()) {
                ts = works[j].start;
            } else {
                auto t = pq.top();
                // cout << "t.top() " << t << endl;
                pq.pop();
                res[idx++] = t.index;
                // cout << "res: ", print(res);
                // cout << "idx:" << t.index << " ";
                ts += t.duration;
            }
            // cout << " ts:" << ts << endl;
        }
        return res;
    }
};

int main() {
    vector<vector<int>> nums = {{1, 2},
                                {2, 4},
                                {3, 2},
                                {4, 1}};
    auto s = Solution();
    auto v = s.getOrder(nums);
    for_each(v.begin(), v.end(), [](int x) { cout << x << " "; });
    return 0;
}