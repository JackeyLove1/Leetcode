#include <unordered_map>
#include <unordered_set>
#include <map>
#include <iostream>
#include <utility>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>
#include <queue>
#include <set>
#include <tuple>
#include <list>
#include <atomic>
#include <thread>

#include <cstring>
#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

template<typename T>
static inline void print(const vector<T> &nums) {
    if (nums.empty()) {
        cout << " empty !" << endl;
        return;
    }
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

inline int count(int state) {
    return __builtin_popcount(state);
}

class Solution {
public:
    vector<int> peopleIndexes(vector<vector<string>> &favoriteCompanies) {
        for (auto &vec : favoriteCompanies) {
            sort(vec.begin(), vec.end());
        }
        vector<int> res;
        for (int i = 0; i < favoriteCompanies.size(); ++i) {
            bool flag = false;
            for (int j = 0; j < favoriteCompanies.size(); ++j) {
                if (i == j) continue;
                if (std::includes(favoriteCompanies[j].begin(), favoriteCompanies[j].end(),
                                  favoriteCompanies[i].begin(), favoriteCompanies[i].end())) {
                    flag = true;
                    break;
                }
            }
            if (!flag) res.push_back(i);
        }
        return res;
    }
};