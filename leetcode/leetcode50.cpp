#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <functional>
#include <queue>
#include <set>

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
    cout << "ending .... " << endl;
}

using PII = pair<int, int>;

inline void print(vector<PII> &nums) {
    for (auto &num : nums) {
        cout << num.first << " " << num.second << endl;
    }
}

int atoi(string &s) {
    int res = 0;
    int sign = (s[0] == '-') ? -1 : 1;
    for (auto &num : s) {
        if (num == '-') continue;
        res *= 10;
        res += num - '0';
    }
    return res * sign;
}

int evalRPN(vector<string> &tokens) {
    vector<int> st;
    for (auto &str : tokens) {
        if (str.size() == 1 && !isdigit(str[0])) {
            int a = st.back();
            st.pop_back();
            int b = st.back();
            st.pop_back();
            int c;
            if (str == "*") {
                c = a * b;
            } else if (str == "/") {
                c = b / a;
            } else if (str == "+") {
                c = a + b;
            } else {
                c = b - a;
            }
            st.push_back(c);
        } else {
            st.push_back(atoi(str));
        }
    }
    return st.front();
}

int main() {
    vector<string> v1 = {"2", "1", "+", "3", "*"};
    cout << evalRPN(v1) << " res:9" << endl;
    vector<string> v2 = {"4", "13", "5", "/", "+"};
    cout << evalRPN(v2) << " res:6" << endl;
    vector<string> v3 = {"3", "-4", "+"};
    cout << evalRPN(v3) << " res:-1" << endl;
}