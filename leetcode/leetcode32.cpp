#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <queue>
#include <set>
#include <stack>

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

int longestValidParentheses(string s) {
    int ans = 0;
    stack<int> stk;
    stk.push(-1);
    for(int i = 0; i < s.size(); i++){
        if(s[i]=='(')
            stk.push(i);
        else{
            stk.pop();
            if(stk.empty())
                stk.push(i);
            ans = max(ans,i-stk.top());
        }

    }

    return ans;
}

int main(){
    cout << longestValidParentheses("(()") <<" res: 2" << endl;
    cout << longestValidParentheses("(())") <<" res: 4" << endl;
}