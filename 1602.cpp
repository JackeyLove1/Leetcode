#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <set>
#include <queue>

using namespace std;

class WordsFrequency {
public:
    unordered_map<string, int> hash;

    WordsFrequency(vector<string> &book) {
        for (auto b : book) {
            if (hash.find(b) == hash.end())
                hash[b] = 1;
            else
                hash[b]++;
        }
    }

    int get(string word) {
        if (hash.find(word) == hash.end())
            return 0;
        return hash[word];
    }
};

/**
 * Your WordsFrequency object will be instantiated and called as such:
 * WordsFrequency* obj = new WordsFrequency(book);
 * int param_1 = obj->get(word);
 */