class Solution {
public:
    bool checkIfExist(vector<int> &arr) {
        unordered_map<int, int> m;
        for (auto &num : arr) {
            ++m[num];
        }
        for (auto &[k, v] : m) {
            if (k == 0 && v > 1) return true;
            if (k != 0 && m.count(k * 2)) return true;
        }
        return false;
    }
};