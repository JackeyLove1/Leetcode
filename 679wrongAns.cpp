#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <stack>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Node {
public:
    int val;
    vector<Node *> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node *> _children) {
        val = _val;
        children = _children;
    }
};

void swap(double &x, double &y) {
    double temp = x;
    x = y;
    y = temp;
}

unordered_map<pair<double, double>, vector<double>> hash1;

vector<double> make2Number(double x, double y, unordered_map<pair<double, double>, vector<double>> &hash) {
    if (x > y) swap(x, y);
    auto temp = pair<double, double>(x, y);
    if (hash.find(temp) != hash.end())
        return hash[temp];
    vector<double> res;
    res.push_back(x + y);
    res.push_back(x - y);
    res.push_back(x * y);
    res.push_back(x / y);
    res.push_back(y / x);
    hash[temp] = res;
    return res;
}

bool judge2(double x, double y) {
    if (abs(x + y - 24) < 0.01 ||
        abs(x * y - 24) < 0.01 ||
        abs(x - y - 24) < 0.01 ||
        (y != 0 && abs(x / y - 24) < 0.01) ||
        (x != 0 && abs(y / x - 24) < 0.01))
        return true;
    return false;
}

bool judge3Numbers(double x, double y, double z) {
    vector<double> temp1 = make2Number(x, y, hash1);
    for (auto num : temp1) {
        if (judge2(num, z))
            return true;
    }
    vector<double> temp2 = make2Number(x, z, hash1);
    for (auto num : temp2) {
        if (judge2(num, y))
            return true;
    }
    vector<double> temp3 = make2Number(z, y, hash1);
    for (auto num : temp3) {
        if (judge2(num, x))
            return true;
    }
    return false;
}

bool judgePoint24(vector<int> &nums) {
    
}

