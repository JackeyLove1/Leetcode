#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <bitset>
#include <cstring>
#include <queue>

using namespace std;
constexpr int N = 100;
const int debug = 1;

int innnerLength(vector<vector<int>> &binaryImage) {
    int n = binaryImage.size();
    int m = binaryImage[0].size();
    int res = 0;
    vector<vector<int>> f(n + 1, vector<int>(m + 1, 1));
    for (int i = 0; i < n; ++i) {
        for (int j = 1; j < m; ++j) {
            if (binaryImage[i][j] == binaryImage[i][j - 1]) {
                f[i][j] = f[i][j - 1] + 1;
            }
        }
    }
    // lambda function
    function<int(int)> check = [&](int idx) -> int {
        int start = -1, end = -1, freq = -1;
        for (int i = 0; i < n; ++i) {
            if (binaryImage[i][idx] == 1) {
                start = i;
                break;
            }
        }
        if (start == -1 || start == n - 1) return 0;
        if (binaryImage[start + 1][idx] == 1) return 0;
        freq = f[start + 1][idx];
        for (int i = start + 1; i < n; ++i) {
            if (binaryImage[i][idx] == 1) {
                end = i;
                break;
            } else {
                if (f[i][idx] != freq)
                    return 0;
            }
        }
        return freq * 2 + (end - start - 1) * 2;
    };
    for (int i = m - 1; i >= 0; --i) {
        res = check(i);
        if (res != 0) return res;
    }
    return res;
}

int main() {
    vector<vector<int>> nums = {
            {1, 1, 1, 1},
            {1, 0, 0, 1},
            {1, 1, 1, 1},
            {0, 0, 0, 0}
    };
    auto res = innnerLength(nums);
    cout << res << " res: 6" << endl;
    vector<vector<int>> nums2 = {
            {0, 1, 0},
            {1, 0, 1},
            {1, 0, 1},
            {1, 0, 1},
            {0, 0, 0}
    };
    cout << innnerLength(nums2) << " res: 0" << endl;
    vector<vector<int>> nums3 = {
            {0, 1, 0},
            {1, 0, 1},
            {1, 0, 1},
            {1, 0, 1},
            {0, 1, 0}
    };
    cout << innnerLength(nums3) << " res: 8" << endl;
    return 0;
}