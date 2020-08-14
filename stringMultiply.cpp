#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <cmath>

using namespace std;

vector<int> str2int(string nums) {
    vector<int> v;
    for (auto num : nums) {
        v.push_back(num - '0');
    }
    return v;
}

vector<int> vecMultiply(vector<int> &A, vector<int> &B) {
    vector<int> res;
    int i = 0, j = 0, carry = 0;
    int m = A.size(), n = B.size();
    while (i < m || j < n) {
        int x = (i < m) ? A[i++] : 0;
        int y = (j < n) ? B[j++] : 0;
        int tmp = x + y +carry;
        if(tmp > 9){
            carry = tmp - 9;
            res.push_back(9);
        } else
            res.push_back(tmp);
    }
    if(carry > 0){
        while (carry > 0){
            res.push_back(carry%10);
            carry = carry / 10;
        }
    }
    while (res.back() == 0)
        res.pop_back();
    return res;
}

string multiply(string num1, string num2) {
    vector<int> n1 = str2int(num1);
    vector<int> n2 = str2int(num2);
    vector<int> res = vecMultiply(n1, n2);
    reverse(res.begin(), res.end());
    string s = "";
    while (!res.empty()){
        s += '0'+res.back();
        res.pop_back();
    }
    return s;
}