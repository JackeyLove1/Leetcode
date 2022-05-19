//
// Created by Jacky on 2022/5/18.
//

#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include <cassert>

using namespace std;

class Trie {
public:
    explicit Trie() : children(26, nullptr), cnt_(0) {}

    void insert(const std::string &word) {
        Trie *node = this;
        for (const auto &c : word) {
            int idx = c - 'a';
            if (node->children[idx] == nullptr) {
                node->children[idx] = new Trie();
            }
            node = node->children[idx];
        }
        node->cnt_ += 1;
    }

    int search(const std::string &word) {
        Trie *node = this;
        for (const auto &c : word) {
            int idx = c - 'a';
            if (node->children[idx] == nullptr) {
                return 0;
            }
            node = node->children[idx];
        }
        return node->cnt_;
    }

    bool startWith(const std::string &prefix) {
        Trie *node = this;
        for (const auto &c : prefix) {
            int idx = c - 'a';
            if (node->children[idx] == nullptr) {
                return false;
            }
            node = node->children[idx];
        }
        return true;
    }

private:
    std::vector<Trie*> children;
    int cnt_;
};

int main() {
    Trie trie;
    vector<string> words = {"abc", "123", "fhj"};
    for (const auto &w : words) {
        trie.insert(w);
    }
    for (const auto &w : words) {
        assert(trie.search(w) == 1);
        assert(trie.startWith(w.substr(0, 1)));
        // cout << w.substr(0, 1) << endl;
    }
    assert(trie.search("1234") == 0);

    cout << "Test Succeed!" << endl;
    return 0;
}