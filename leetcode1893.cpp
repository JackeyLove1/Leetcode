#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for (auto &num : nums) cout << num << " ";
    cout << endl;
}

template<typename T>
inline void print(vector<vector<T>> &nums) {
    for (auto &num : nums) {
        for (auto &n : num) {
            cout << n << " ";
        }
        cout << endl;
    }
    cout << "ending ... " << endl;
}

class Node {
public:
    int val;
    Node *next;
    Node *random;

    Node(int _val) {
        val = _val;
        next = nullptr;
        random = nullptr;
    }
};

bool isCovered0(vector<vector<int>> &ranges, int left, int right) {
    if (ranges.empty()) return false;
    sort(ranges.begin(), ranges.end(), [](const vector<int> &v1, const vector<int> &v2) {
        if (v1[0] == v2[0]) {
            return v1[1] < v2[1];
        }
        return v1[0] < v2[0];
    });
    vector<vector<int>> merge;
    int st = ranges[0][0], ed = ranges[0][1];
    for (auto &r : ranges) {
        if (st <= r[0] && r[1] <= ed) {
            continue;
        } else if (r[0] > ed) {
            merge.push_back({st, ed});
            st = r[0], ed = r[1];
        } else {
            st = min(st, r[0]);
            ed = max(ed, r[1]);
        }
    }
    if (merge.back()[1] != ed) {
        merge.push_back({st, ed});
    }
    if (left < merge.front()[0] || right > merge.back()[1]) {
        return false;
    }
    for (auto &m : merge) {
        if (left >= m[0] && right <= m[1]) {
            return true;
        }
    }
    return false;
}

bool isCovered(vector<vector<int>> &ranges, int left, int right) {
    if (ranges.empty()) return false;
    int p = left, cnt = 0;
    sort(ranges.begin(), ranges.end(), [](const vector<int> &v1, const vector<int> &v2) {
        if (v1[0] == v2[0]) {
            return v1[1] < v2[1];
        }
        return v1[0] < v2[0];
    });
    for (auto &r : ranges) {
        while (r[0] <= p && p <= r[1]) {
            p++, cnt++;
        }
        if (cnt >= right - left + 1) return true;
    }
    return false;
}

int main() {
    vector<vector<int>> ranges = {{1,10},{10,20}};
    int left = 21, right = 21;
    cout << isCovered(ranges, left, right) << endl;
}