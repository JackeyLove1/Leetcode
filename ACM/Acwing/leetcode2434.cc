#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <numeric>
#include <cmath>

using namespace std;
using sll = __int128;
using ull = unsigned long long;
using ll = long long;
using PII = pair<int, int>;

class Solution {
public:
    string robotWithString(string s) {
        if (s.size() <= 1) return s;
        map<char, int> idx;
        for (int i = s.size() - 1; i >= 0; --i){
            if (idx.find(s[i]) == idx.end()){
                idx[s[i]] = i;
            }
        }
        string res{};
        vector<char> t;
        vector<bool> st(s.size(), false);
        int i = 0;
        for (int tmp = 0; tmp < 26; ++tmp){
            char c = tmp + 'a';
            if (idx.find(c) == idx.end()) continue;
            while (!t.empty() && t.back() <= c){
                res.push_back(t.back());
                // cout <<"c: " << c <<" t.back(): " << t.back() << endl;
                t.pop_back();
            }
            while (i <= idx[s[i]]){
                if (st[i]) continue;
                if (s[i] == c){
                    res.push_back(s[i]);
                    // cout << "s[i]: " << s[i] << endl;
                    st[i] = true;
                }else{
                    t.push_back(s[i]);
                    st[i] = true;
                }
                ++i;
            }
        }
        while (!t.empty()){
            res.push_back(t.back());
            // cout << "push: " << t.back() << endl;
            t.pop_back();
        }
        return res;
    }
};

int main(){
    Solution s{};
    string s1{"zza"};
    // cout << s.robotWithString(s1) <<" res: azz"<< endl;
    // cout << s.robotWithString("bdda") <<" res: addb" << endl;
    // cout << s.robotWithString("bac") <<" res: abc" << endl;
    cout << s.robotWithString("vzhofnpo") << " res: fnohopzv" << endl;
    return 0;
}