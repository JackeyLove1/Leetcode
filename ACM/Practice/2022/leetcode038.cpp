class Solution {
public:
    vector<int> dailyTemperatures(vector<int> &temperatures) {
        int sz = temperatures.size();
        vector<int> f(sz, 0);
        vector<int> st;
        for (int i = 0; i < sz; ++i) {
            if (st.empty()) {
                st.push_back(i);
                continue;
            }
            while (!st.empty() && temperatures[st.back()] < temperatures[i]) {
                f[st.back()] = i - st.back();
                st.pop_back();
            }
            st.push_back(i);
        }
        for (const auto &index : st) {
            f[index] = 0;
        }
        return f;
    }
};