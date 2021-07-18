#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;

int main(){
    unordered_map<int, int>um;
    string s;
    char ch;
    // cin >> s >> ch;
    getline(cin , s);
    cin >> ch;
    cout << "s: " << s << endl;
    cout << "ch: "<<ch << endl;
    for(auto & str : s){
        if(str >= 'a' && str <= 'z'){
            um[str - 'a']++;
        }
        if(str >= 'A' && str <= 'Z'){
            um[str - 'A']++;
        }
    }
    int res = 0;
    if (ch >= 'a' && ch <= 'z'){
        res = um[ch - 'a'];
    }
    if(ch >= 'A' && ch <= 'Z'){
        res = um[ch - 'A'];
    }
    cout << res << endl;
    return 0;
}