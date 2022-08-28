#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

static inline int read() {
    int x = 0, f = 0, ch;
    while (!isdigit(ch = getchar())) f |= ch == '-';
    while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    return f ? -x : x;
}

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

using ull = unsigned long long;
using LL = long long;
using PII = pair<int, int>;

constexpr int N = 5510, INF = 1e9;

int main(){
    fhj();
    string s;
    cin >> s;
    unordered_map<char, int> um;
    int unk = 0;
    if (s.size() < 26){
        cout << -1 << endl;
        return 0;
    }
    for (int i = 0; i < 26; ++i){
        if (s[i] == '?') unk++;
        else {
            um[s[i]]++;
        }
     }
    auto flag = (unk + um.size()) == 26;
    int i = 0, j = 26;
    for (; !flag && j < s.size(); i++, j++){
        if (s[j] == '?') ++unk;
        else ++um[s[j]];
        if (s[i] == '?') --unk;
        else {
            if (--um[s[i]] == 0){
                um.erase(s[i]);
            }
        }
        flag = (unk + um.size()) == 26;
    }
    for (int k = 0; flag && k < s.size(); ++k){
       if (k >= i && k < j){
           if(s[k] != '?') cout << s[k];
           else {
               for(int l = 0; l < 26; ++l){
                   char tmp = 'A' + l;
                   if (!um.count(tmp)){
                       cout << (tmp);
                       um[tmp]++;
                       break;
                   }
               }
           }
       }else {
           if (s[k]!='?') cout << s[k];
           else cout << 'A';
       }

    }
    if (!flag) cout << -1;
    cout << endl;
    return 0;
}