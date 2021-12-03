#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

vector<int> partitionLabels(string S) {
    vector<int> place;
    vector<int> res;
    if(S.empty()) return res;
    int right = 0;
    for (int i = 0; i < S.size(); i++) {
        int it = S.find_last_of(S[i]);
        right = (it > right) ? it : right;
        if (i == right) {
            place.push_back(right + 1);
        }
    }
    res.push_back(place[0]);
    for (int i = 0; i < place.size() - 1; i++) {
        res.push_back(place[i + 1] - place[i]);
    }
    return res;
}

void print(vector<int> &res) {
    for (auto num : res) {
        cout << num << " ";
    }
}

int main() {
    string s = "ababcbacadefegdehijhklij";
    vector<int> res = partitionLabels(s);
    print(res);
}