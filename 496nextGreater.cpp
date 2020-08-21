#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <stack>

using namespace std;

vector<int> nextGreaterElement(vector<int> &nums1, vector<int> &nums2) {
    // 使用单调栈
    // nums中没有重复元素
    unordered_map<int, int> hash;
    stack<int> st;
    for (int i = nums2.size()-1; i >=0 ; i--) {
        while (!st.empty() && st.top() <= nums2[i]){
            st.pop();
        }
        hash[nums2[i]] = st.empty() ? -1 : st.top();
        st.push(nums2[i]);
    }
    for(int i = 0;i<nums1.size();i++){
        nums1[i] = hash[nums1[i]];
    }
    return nums1;
}