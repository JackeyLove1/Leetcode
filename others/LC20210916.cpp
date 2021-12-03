// Author: Jacky
// Time: 2021-09-16
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <map>
#include <set>
#include <bitset>
#include <cstring>
#include <queue>
#include <tuple>
#include <deque>

using namespace std;

// LC3
class Solution3 {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> m;
        int l = -1, res = 0;
        for (int r = 0; r < s.size(); ++r) {
            ++m[s[r]];
            while (m[s[r]] > 1 && l < r) {
                ++l;
                --m[s[l]];
            }
            res = max(res, r - l);
        }
        return res;
    }
};

// LC5
class Solution5 {
public:
    string longestPalindrome(string s) {
        int n = s.size();
        if (n == 0 || n == 1) return s;
        int start = 0, maxl = 1;
        vector<vector<int>> f(n + 10, vector<int>(n + 10, 0));
        for (int i = 0; i < n; ++i) {
            f[i][i] = 1;
        }
        for (int i = 1; i < n; ++i) {
            if (s[i] == s[i - 1]) {
                f[i - 1][i] = 1;
                start = i - 1;
                maxl = 2;
            }
        }
        for (int l = 3; l <= n; ++l) {
            for (int i = 0; i + l - 1 < n; ++i) {
                int j = i + l - 1;
                if (s[i] == s[j] && f[i + 1][j - 1]) {
                    maxl = j - i + 1;
                    start = i;
                    f[i][j] = 1;
                }
            }
        }
        return s.substr(start, maxl);
    }
};

// LC11
class Solution11 {
public:
    int maxArea(vector<int> &height) {
        int n = height.size();
        int l = 0, r = n - 1;
        int res = 0;
        while (l < r) {
            res = max(res, min(height[l], height[r]) * (r - l));
            if (height[l] < height[r]) {
                ++l;
            } else {
                --r;
            }
        }
        return res;
    }
};

struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// LC19
class Solution19 {
public:
    ListNode *removeNthFromEnd(ListNode *head, int n) {
        auto dummy = new ListNode(-1, head);
        auto cur = head, pre = dummy;
        int len = 0;
        while (cur != nullptr) {
            cur = cur->next;
            ++len;
        }
        for (int i = 0; i < len - n; ++i) {
            pre = pre->next;
        }
        pre->next = pre->next->next;
        return dummy->next;
    }
};

// LC18
class Solution18v1 {
public:
    vector<vector<int>> fourSum(vector<int> &nums, int target) {
        sort(nums.begin(), nums.end());
        using PII = pair<int, int>;
        unordered_map<int, vector<PII>> m;
        vector<vector<int>> res;
        set<vector<int>> s1;
        set<vector<int>> s2;
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                m[nums[i] + nums[j]].push_back({i, j});
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int k = target - nums[i] - nums[j];
                if (m.count(k)) {
                    auto v = m[k];
                    for (auto&[p1, p2] : v) {
                        if (p1 == i || p1 == j || p2 == i || p2 == j) {
                            continue;
                        }
                        vector<int> tmp1 = {i, j, p1, p2};
                        sort(tmp1.begin(), tmp1.end());
                        if (s1.count(tmp1)) continue;
                        vector<int> tmp2 = {nums[tmp1[0]], nums[tmp1[1]], nums[tmp1[2]], nums[tmp1[3]]};
                        if (s2.count(tmp2)) continue;
                        s1.insert(tmp1);
                        s2.insert(tmp2);
                    }
                }
            }
        }
        vector<vector<int>> v(s2.begin(), s2.end());
        return v;
    }
};

template<typename T>
inline void print(vector<T> &nums) {
    for (auto &num : nums) {
        cout << num << ' ';
    }
    cout << endl;
}

// LC18v2
class Solution18 {
public:
    vector<vector<int>> fourSum(vector<int> &nums, int target) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        vector<vector<int>> res;
        if (n < 4) return res;
        set<vector<int>> s;
        for (int a = 0; a <= n - 4; ++a) {
            if (a > 0 && nums[a - 1] == nums[a]) continue;
            for (int b = a + 1; b <= n - 3; ++b) {
                if (b > a + 1 && nums[b - 1] == nums[b]) continue;
                int c = b + 1, d = n - 1;
                int k = target - nums[a] - nums[b];
                while (c < d) {
                    int partSum = nums[c] + nums[d];
                    if (partSum == k) {
                        vector<int> tmp = {nums[a], nums[b], nums[c], nums[d]};
                        // print(tmp);
                        if (s.count(tmp)) continue;
                        s.emplace(tmp);
                        ++c, --d;
                    } else if (partSum < k) {
                        ++c;
                    } else {
                        --d;
                    }
                }
            }
        }
        vector<vector<int>> v(s.begin(), s.end());
        return v;
    }
};

// LC16
class Solution16 {
public:
    int threeSumClosest(vector<int> &nums, int target) {
        int res = -1e6;
        sort(nums.begin(), nums.end());
        function<void(int)> update = [&](int sum) {
            if (abs(sum - target) < abs(res - target)) {
                res = sum;
            }
        };

        for (int a = 0; a < nums.size(); ++a) {
            if (a > 0 && nums[a] == nums[a - 1]) continue;
            int b = a + 1, c = nums.size() - 1;
            while (b < c) {
                int t = nums[a] + nums[b] + nums[c];
                update(t);
                if (t == target) {
                    return t;
                } else if (t > target) {
                    int cur = nums[c];
                    --c;
                    while (b < c && cur == nums[c]) --c;
                } else {
                    int cur = nums[b];
                    ++b;
                    while (b < c && cur == nums[b]) ++b;
                }
            }
        }
        return res;
    }
};

// LC12
class Solution12 {
public:
    string intToRoman(int num) {
        using PIS = pair<int, string>;
        vector<PIS> v = {{1000, "M"},
                         {900,  "CM"},
                         {500,  "D"},
                         {400,  "CD"},
                         {100,  "C"},
                         {90,   "XC"},
                         {50,   "L"},
                         {40,   "XL"},
                         {10,   "X"},
                         {9,    "IX"},
                         {5,    "V"},
                         {4,    "IV"},
                         {1,    "I"}};
        string res = "";
        for (auto&[n, str] : v) {
            while (num >= n) {
                num -= n;
                res += str;
            }
            if (num == 0) break;
        }
        return res;
    }
};

// LC25
class Solution25 {
public:
    using PLL = pair<ListNode *, ListNode *>;

    PLL reverse(ListNode *head, ListNode *tail) {
        tail->next = nullptr;
        ListNode *pre = nullptr;
        auto cur = head;
        while (cur != nullptr) {
            auto next = cur->next;
            cur->next = pre;
            pre = cur;
            cur = next;
        }
        head->next = nullptr;
        return {tail, head};
    }


    ListNode *reverseKGroup(ListNode *head, int k) {
        auto dummy = new ListNode(-1, head);
        auto cur = dummy;
        while (cur != nullptr) {
            auto l = cur->next, r = cur;
            for (int i = 0; i < k; ++i) {
                r = r->next;
                if (r == nullptr) return dummy->next;
            }
            auto next = r->next;
            r->next = nullptr;
            auto[ln, rn] = reverse(l, r);
            cur->next = ln;
            rn->next = next;
            cur = rn;
        }
        return dummy->next;
    }
};

// LC54
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution54 {
public:
    vector<int> v;

    void solve(TreeNode *root) {
        if (root == nullptr) return;
        solve(root->right);
        v.push_back(root->val);
        solve(root->left);
    }

    int kthLargest(TreeNode *root, int k) {
        solve(root);
        return v[k - 1];
    }
};

// LC43
class Solution43 {
public:
    vector<int> mul(vector<int> &A, vector<int> &B) {
        vector<int> C(A.size() + B.size(), 0);
        for (int i = 0; i < A.size(); ++i) {
            for (int j = 0; j < B.size(); ++j) {
                C[i + j] += A[i] * B[j];
            }
        }
        int t = 0;
        for (int i = 0; i < C.size(); ++i) {
            t += C[i];
            C[i] = t % 10;
            t /= 10;
        }
        while (C.size() > 1 && C.back() == 0) C.pop_back();
    }

    string multiply(string num1, string num2) {
        vector<int> A, B;
        for (int i = num1.size() - 1; i >= 0; i--) A.push_back(num1[i] - '0');
        for (int i = num2.size() - 1; i >= 0; i--) B.push_back(num2[i] - '0');
        vector<int> C = mul(A, B);
        string res = "";
        for (int i = C.size() - 1; i >= 0; i--) {
            res.push_back(C[i] + '0');
        }
        return res;
    }
};

// LC1143
class Solution1143 {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int n = text1.size(), m = text2.size();
        vector<vector<int>> f(n + 10, vector<int>(m + 10, 0));
        for (int i = 1; i <= n; ++i) {
            char ch1 = text1[i - 1];
            for (int j = 1; j <= m; ++j) {
                char ch2 = text2[j - 1];
                if (ch1 == ch2) {
                    f[i][j] = max(f[i][j], f[i - 1][j - 1] + 1);
                } else {
                    f[i][j] = max(f[i - 1][j], f[i][j - 1]);
                }
            }
        }
        return f[n][m];
    }
};
