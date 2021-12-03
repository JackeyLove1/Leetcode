using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

int minDepth(TreeNode *root) {
    if (root == nullptr) return 0;
    if (root->left == nullptr && root->right == nullptr) return 1;
    if (root->right == nullptr && root->left != nullptr)
        return 1 + minDepth(root->left);
    if (root->right != nullptr && root->left == nullptr)
        return 1 + minDepth(root->right);
    return 1 + min(minDepth(root->left), minDepth(root->right));
}