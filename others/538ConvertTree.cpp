void traverse(TreeNode *root, set<int> &s) {
    if (root == nullptr) return;
    s.insert(root->val);
    traverse(root->left, s);
    traverse(root->right, s);
}

void helper(unordered_map<int, int> &hash, set<int> &s, vector<int> &vec) {
    vec.assign(s.begin(), s.end());
    sort(vec.begin(), vec.end());
    for (int i = 0; i < vec.size(); i++) {
        hash[vec[i]] = 0;
        for (int j = i + 1; j < vec.size(); j++) {
            hash[vec[i]] += vec[j];
        }
    }
}

TreeNode *convert(TreeNode *root, unordered_map<int, int> &hash) {
    if (root == nullptr) return nullptr;
    root->val = hash[root->val];
    root->left = convert(root->left, hash);
    root->right = convert(root->right, hash);
    return root;
}

TreeNode *convertBST(TreeNode *root) {
    if (root == nullptr) return nullptr;
    unordered_map<int, int> hash;
    set<int> s;
    vector<int> vec;
    auto p = &root;
    traverse(*p, s);
    helper(hash, s, vec);
    return convert(root, hash);
}