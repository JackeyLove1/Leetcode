// Author: Jacky
// Time: 2021-09-22
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

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
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
    // cout << "ending ... " << endl;
}

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

int solve(int num) {
    vector<int> nums;
    bool postive = num > 0;
    num = postive ? num : (-num);
    int five = 0;
    while (num) {
        int left = num % 10;
        if (left == 5) ++five;
        nums.push_back(left);
        num /= 10;
    }
    reverse(nums.begin(), nums.end());
    vector<bool> flag(nums.size(), true);
    std::function<int()> cal = [&]() -> int {
        int res = 0;
        if (!postive) {
            reverse(nums.begin(), nums.end());
            reverse(flag.begin(), flag.end());
        }
        for (int i = 0; i < nums.size(); ++i) {
            if (!flag[i]) continue;
            res = res * 10 + nums[i];
        }
        return res;
    };

    if (five == 1) {
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] == 5) {
                flag[i] = false;
                break;
            }
        }
        return cal();
    }

    std::function<int()> work = [&]() -> int {
        for (int i = 0; i < nums.size() - 1; ++i) {
            if (nums[i] == 5 && nums[i] < nums[i + 1]) {
                flag[i] = false;
                break;
            }
        }
        return cal();
    };

    if (postive) {
        return work();
    } else {
        reverse(nums.begin(), nums.end());
        reverse(flag.begin(), flag.end());
        return -work();
    }
}

int main() {
    cout << solve(15958) << " res: 1958" << endl;
    cout << solve(-5859) << " res: -589" << endl;
    cout << solve(-15859) << " res: -1589" << endl;
    cout << solve(1555958) << " res: 155958" << endl;
    cout << solve(-5000) << " res: 0" << endl;
}

/*
// Author: Jacky
// Time: 2021-09-22
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

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
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
    // cout << "ending ... " << endl;
}

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

int solve(int num) {
    bool postive = num > 0;
    num = postive ? num : -num;
    string s = to_string(num);
    vector<bool> flag(s.size(), false);
    vector<int> res;
    function<void()> work = [&]() {
        int sum = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (flag[i]) continue;
            sum = sum * 10 + (s[i] - '0');
        }
        res.push_back(sum);
    };
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '5' && i == 0) {
            flag[i] = true;
            work();
            flag[i] = false;
        } else if (s[i] == '5' && i > 0 && s[i - 1] != '5') {
            flag[i] = true;
            work();
            flag[i] = false;
        }
    }
    if (postive) {
        return *max_element(res.begin(), res.end());
    } else {
        return -(*min_element(res.begin(), res.end()));
    }
}

int main() {
    cout << solve(15958) << " res: 1958" << endl;
    cout << solve(-5859) << " res: -589" << endl;
    cout << solve(-15859) << " res: -1589" << endl;
    cout << solve(1555958) << " res: 155958" << endl;
    cout << solve(-5000) << " res: 0" << endl;
}
*/