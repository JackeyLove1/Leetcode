#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

class Node {
public:
    int val;
    vector<Node *> neighbors;

    Node() {
        val = 0;
        neighbors = vector<Node *>();
    }

    Node(int _val) {
        val = _val;
        neighbors = vector<Node *>();
    }

    Node(int _val, vector<Node *> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

// judge the differences of two strings
// all the strings's length are the same
bool connect(string word1, string word2) {
    int diff = 0;
    for (int i = 0; i < word1.size(); i++) {
        if (word1[i] != word2[i])
            diff++;
        if (diff > 1)
            return false;
    }
    return diff == 1;
}

// construct the graph
void construct_graph(const string beginWord, vector<string> &wordList, unordered_map<string, vector<string>> &graph) {
    wordList.push_back(beginWord);
    for (int i = 0; i < wordList.size(); i++) {
        for (int j = i + 1; j < wordList.size(); j++) {
            if (connect(wordList[i], wordList[j])) {
                graph[wordList[i]].push_back(wordList[j]);
                graph[wordList[j]].push_back(wordList[i]);
            }
        }
    }
}

//void print(unordered_map<string, vector<string>> graph) {
//    for (auto str : graph) {
//        cout << str.first << endl;
//        for (auto s : str.second) {
//            cout << s << "  ";
//        }
//        cout << endl;
//    }
//}
//
//void print(vector<string> v) {
//    for (auto str:v)
//        cout << str << "  ";
//    cout << endl;
//}

// solve the problem
int ladderLength(string beginWord, string endWord, vector<string> &wordList) {
    unordered_set<string> visited;
    unordered_map<string, vector<string>> graph;
    construct_graph(beginWord, wordList, graph);
    // print(graph);
    queue<string> bfs;
    const string target = endWord;
    bfs.push(beginWord);
    visited.insert(beginWord);
    int level = 1;
    while (!bfs.empty()) {
        int size = bfs.size();
        for (int i = 0; i < size; i++) {
            string tmp_node = bfs.front();
            bfs.pop();
            // record
            // print(graph[tmp_node]);
            for (auto neighbor : graph[tmp_node]) {
                if (visited.find(neighbor) == visited.end()) {
                    // cout << neighbor << endl;
                    bfs.push(neighbor);
                    visited.insert(neighbor);
                }
                if (neighbor == target) return level + 1;
            }
        }
        level++;
    }
    return 0;
}

int main() {
    string begin = "hit";
    string end = "cog";
    vector<string> wordList = {"hot", "dot", "dog", "lot", "log", "cog"};
    cout << ladderLength(begin, end, wordList) << endl;
    vector<string> v({"a", "b", "c"});
    cout << ladderLength("a", "c", v);
    return 0;
}