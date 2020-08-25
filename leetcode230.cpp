vector<int> nums;
void traverse(TreeNode* root){
    if(root == nullptr) return ;
    traverse(root->left);
    nums.push_back(root->val);
    traverse(root->right);
}
int kthSmallest(TreeNode* root, int k) {
    traverse(root);
    return nums[k-1];
}