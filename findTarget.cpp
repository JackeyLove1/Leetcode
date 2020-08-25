vector<int> nums;

void traverse(TreeNode *root) {
    if (root == nullptr) return;
    traverse(root->left);
    nums.push_back(root->val);
    traverse(root->right);
}

bool findTarget(TreeNode *root, int k) {
    traverse(root);
    int n = nums.size();
    int i = 0, j = n - 1;
    while (i < j) {
        if (nums[i] + nums[j] == k) return true;
        if (nums[i] + nums[j] > k) j--;
        if (nums[i] + nums[j] < k) i++;
    }
    return false;
}