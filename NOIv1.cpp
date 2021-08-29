#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
#include <unordered_map>
#include <numeric>
#include <stack>

using namespace std;

class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 给定一个字符串保存在 string 类型中，返回字符串中最长的无重复子字符串的长度
     * @param s string字符串 输入的字符串
     * @return int整型
     */
    bool check(unordered_map<char, int> &m) {
        for (auto&[k, v] : m) {
            if (v > 1) return false;
        }
        return true;
    }

    int lengthOfLongestSubstring(string s) {
        // write code here
        unordered_map<char, int> m;
        int j = 0, n = s.size();
        int res = 0;
        for (int i = 0; i < n; i++) {
            ++m[s[i]];
            while (j < i && !check(m)) {
                --m[s[j++]];
            }
            res = max(res, i - j + 1);
        }
        return res;
    }
};

class Parenthesis {
public:
    bool chkParenthesis(string A, int n) {
        // write code here
        stack<int> st;
        for (auto &&ch : A) {
            if (ch == '(') {
                st.emplace(ch);
            } else if (ch == ')') {
                if (st.empty()) return false;
                st.pop();
            } else {
                return false;
            }
        }
        return st.empty();
    }
};

class ChkBloodType {
public:
    vector<string> chkBlood(string father, string mother) {
        // write code here
        if (father == "O" && mother == "O") {
            return vector<string>{"O"};
        } else if ((father == "A" && mother == "O") || (father == "O" && mother == "A")) {
            return {"A", "O"};
        } else if ((father == "A" && mother == "A")) {
            return {"A", "O"};
        } else if ((father == "A" && mother == "B") || (father == "B" && mother == "A")) {
            return {"A", "B", "AB", "O"};
        } else if ((father == "A" && mother == "AB") || (father == "AB" && mother == "A")) {
            return {"A", "B", "AB"};
        } else if ((father == "B" && mother == "O") || (father == "O" && mother == "B")) {
            return {"B", "O"};
        } else if ((father == "B" && mother == "B")) {
            return {"B", "O"};
        } else if ((father == "B" && mother == "AB") || (father == "AB" && mother == "B")) {
            return {"A", "B", "AB"};
        } else if ((father == "AB" && mother == "O") || (father == "O" && mother == "AB")) {
            return {"A", "B"};
        } else if ((father == "AB" && mother == "AB")) {
            return {"A", "B", "AB"};
        } else {
            return {};
        }
    }
};

class Solution1 {
public:
    /**
     *
     * @param matrix int整型vector<vector<>> the matrix
     * @return int整型
     */
    int minPathSum(vector<vector<int> > &matrix) {
        // write code here
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> f(m + 1, vector<int>(n + 1, 0));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0 && j > 0) {
                    matrix[i][j] += matrix[i][j - 1];
                } else if (i > 0 && j == 0) {
                    matrix[i][j] += matrix[i - 1][j];
                } else {
                    matrix[i][j] += min(matrix[i - 1][j], matrix[i][j - 1]);
                }
            }
        }
        return matrix[m - 1][n - 1];
    }
};