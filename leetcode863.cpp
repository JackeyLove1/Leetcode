/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution 
{
public:
    unordered_map<TreeNode *, TreeNode *> node_parent;

    //---------- 找到每个非空结点的父节点。本质是完善 邻接表
    void dfs_find_node_parent(TreeNode * node)
    {
        if (node)
        {
            if (node->left)
                node_parent[node->left] = node;
            if (node->right)
                node_parent[node->right] = node;
            dfs_find_node_parent(node->left);
            dfs_find_node_parent(node->right);
        }
    }

    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) 
    {
        dfs_find_node_parent(root);

        if (k == 0)
            return vector<int> {target->val};
        
        vector<int> res;
        //------------------------- bfs波纹法。先visit和先判只适应于0 < k的情况
        queue<TreeNode *> Q;
        unordered_set<TreeNode *> visited;
        Q.push(target);
        visited.insert(target);
        int level = 0;
        while (!Q.empty() && level < k)
        {
            level ++;
            int cur_len = (int)Q.size();
            for (int _ = 0; _ < cur_len; _ ++)
            {
                TreeNode * x = Q.front();    Q.pop();
                for (TreeNode* y : vector<TreeNode*> {node_parent[x], x->left, x->right})
                {
                    if (y && visited.find(y) == visited.end())
                    {
                        if (level == k)
                            res.push_back(y->val);
                        visited.insert(y);
                        Q.push(y);
                    }
                }
            }
        }
        
        return res;
    }
};
