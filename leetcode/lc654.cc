class TreeNode {
public:
    TreeNode *left, *right;
    int val;

    explicit TreeNode() : val(0), left(nullptr), right(nullptr) {}

    explicit TreeNode(int val_) : val(val_), left(nullptr), right(nullptr) {}
};

class Solution {
private:
    TreeNode *constructMaximumBinaryTree(vector<int> &nums, int l, int r) {
        if (l > r) return nullptr;
        if (l == r) return new TreeNode(nums[l]);
        auto iter = max_element(nums.begin() + l, nums.begin() + r + 1);
        auto idx = iter - nums.begin();
        // cout << "idx: " << idx << endl;
        auto *res = new TreeNode(nums[idx]);
        res->left = constructMaximumBinaryTree(nums, l, idx - 1);
        res->right = constructMaximumBinaryTree(nums, idx + 1, r);
        return res;
    }

public:
    TreeNode *constructMaximumBinaryTree(vector<int> &nums) {
        if (nums.empty()) return nullptr;
        return constructMaximumBinaryTree(nums, 0, nums.size() - 1);
    }
};

int main() {
    vector<int> nums = {3, 2, 1, 6, 0, 5};
    Solution s;
    auto res = s.constructMaximumBinaryTree(nums);

}