class Solution {
public:
    vector<int> asteroidCollision(vector<int> &asteroids) {
        vector<int> st;
        for (int num : asteroids) {
            if (st.empty()) {
                st.push_back(num);
                continue;
            }
            if (num < 0) {
                while (!st.empty() && st.back() > 0 && st.back() < abs(num)) {
                    st.pop_back();
                }
                if (st.empty()) {
                    st.push_back(num);
                    continue;
                }
                if (st.back() == abs(num)) {
                    st.pop_back();
                    continue;
                }
                if (st.back() > abs(num)) {
                    continue;
                }
            }
            st.push_back(num);
        }
        return st;
    }
};