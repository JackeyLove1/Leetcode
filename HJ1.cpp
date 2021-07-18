#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main(){
    string s;
    int res = 0;
    while(cin >> s){
        res = s.size();
    }
    cout << res << endl;
    return 0;
}