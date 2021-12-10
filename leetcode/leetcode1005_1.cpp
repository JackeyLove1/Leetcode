#include <unordered_map>
#include <map>
#include <set>
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>


using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

class Solution {
private:
    class Trie {
    public:
        vector<Trie *> children;
        bool isEnd;
        int index;

        Trie *searchPrefix(const string &prefix) {
            Trie *node = this;
            for (char ch : prefix) {
                ch -= 'a';
                if (node->children[ch] == nullptr) {
                    return nullptr;
                }
                node = node->children[ch];
            }
            return node;
        }

    public:
        Trie() : children(26), isEnd(false), index(-1) {}

        void insert(const string &word, int index_) {
            Trie *node = this;
            for (char ch : word) {
                ch -= 'a';
                if (node->children[ch] == nullptr) {
                    node->children[ch] = new Trie();
                }
                node = node->children[ch];
            }
            node->isEnd = true;
            node->index = index_;
        }

        int search(const string &word) {
            Trie *node = this->searchPrefix(word);
            // return node != nullptr && node->isEnd;
            return node->index;
        }

        bool startsWith(const string &prefix) {
            return this->searchPrefix(prefix) != nullptr;
        }
    };

private:
    Trie *t;
public:
    Solution() : t(new Trie()) {}

    int findString(vector<string> &words, string s) {
        for (int i = 0; i < words.size(); ++i) {
            if (s == words[i]) return i;
        }
        return -1;
    }
};