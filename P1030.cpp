#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <bitset>
#include <cstring>
#include <queue>
#include <random>

using namespace std;

string inner, post;
const int debug = 0;

struct TreeNode {
    TreeNode *left;
    TreeNode *right;
    char ch;

    TreeNode(char _ch) : ch(_ch), left(nullptr), right(nullptr) {}
};

unordered_map<int, char> idx;
int cur;

TreeNode *build(int left, int right) {
    if (cur < 0) return nullptr;
    if (left > right) return nullptr;
    auto ch = post[cur];
    auto root = new TreeNode(ch);
    int pos = idx[ch];
    if (debug) {
        cout << "ch: " << ch << " ";
        cout << "pos: " << pos << " ";
        cout << "cur: " << cur << endl;
    }
    --cur;
    root->right = build(pos + 1, right);
    root->left = build(left, pos - 1);
    return root;
}

string pre;

void preOrder(TreeNode *root) {
    if (root == nullptr) return;
    pre.push_back(root->ch);
    preOrder(root->left);
    preOrder(root->right);
}

int main() {
    cin >> inner >> post;
    cur = post.size() - 1;
    for (int i = 0; i < inner.size(); ++i) {
        idx[inner[i]] = i;
    }
    auto root = build(0, post.size() - 1);
    preOrder(root);
    cout << pre << endl;
    return 0;
}