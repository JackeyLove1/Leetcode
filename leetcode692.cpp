#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <functional>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <string>

using namespace std;

struct Node {
    string str;
    int fre;

    Node(string _str, int _fre) {
        str = _str;
        fre = _fre;
    }
};

bool cmp(Node &n1, Node &n2) {
    if (n1.fre != n2.fre)
        return n1.fre > n2.fre;
    else
        return n1.str < n2.str;
}

vector<string> topKFrequent(vector<string> &words, int k) {
    unordered_map<string, int> hash;
    for (auto word : words) {
        hash[word]++;
    }
    vector<Node> vec;
    for (auto[k, v] : hash) {
        vec.push_back(Node(k, v));
    }
    sort(vec.begin(), vec.end(), cmp);
    vector<string> res;
    for (int i = 0; i < k; i++) {
        res.push_back(vec[i].str);
    }
    return res;
}