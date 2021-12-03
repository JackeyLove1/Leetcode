#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <stack>

using namespace std;

vector<int> dailyTemperatures(vector<int> &T) {
    vector<int> ans(T.size(), 0);
    // 构建单调栈, 使用索引入栈
    // 构造单调递减的栈
    stack<int> st;
    for (int i = 0; i < T.size(); i++) {
        while (!st.empty() && T[st.top()] < T[i]){
            ans[st.top()] = i - st.top();
            st.pop();
        }
        st.push(i);
    }
    while (!st.empty()){
        ans[st.top()] = 0;
        st.pop();
    }
    return ans;
}