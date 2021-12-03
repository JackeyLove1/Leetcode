#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <set>
#include <deque>
#include <stdlib.h>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(NULL) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

bool isNumber(string s) {
    if (s == " ") return false;
    if (!s.empty()) {
        s.erase(0, s.find_first_not_of(" "));
        s.erase(s.find_last_not_of(" ") + 1);
    }
    for (auto str :s) {
        if ((str >= '0' && str <= '9') || str == 'e' || str == 'E' || str == '.' || str == '+' || str == '-')
            continue;
        return false;
    }
    int end = s.size() - 1;
    if (isdigit(s[end]) || s[end] == '.') {}
    else return false;
    int dot = 0;
    int e = 0;
    int E = 0;
    int num = 0;
    for (int i = 0; i < s.size(); i++) {
        if (isdigit(s[i])) {
            num++;
            continue;
        }
        switch (s[i]) {
            case '+':
                if (i == 0) break;
                else if (s[i - 1] == 'E' || s[i-1] == 'e') break;
                else return false;
            case '-':
                if (i == 0) break;
                else if (s[i - 1] == 'E'||s[i-1] == 'e') break;
                else return false;
            case 'e':
                if (i == 0 || i == end) return false;
                else if ((isdigit(s[i - 1]) || s[i - 1] == '.') && (isdigit(s[i + 1])||s[i+1] == '+'||s[i+1]== '-' )) {
                    e++;
                    break;
                } else return false;
            case 'E':
                if (i == 0 || i == end) return false;
                else if ((isdigit(s[i - 1]) || s[i - 1] == '.') &&
                         (isdigit(s[i + 1]) || s[i + 1] == '+' || s[i + 1] == '-')) {
                    E++;
                    break;
                } else return false;
            case '.':
                if (e > 0 || E > 0) return false;
                else if (i == 0 && s.size() > 1 && isdigit(s[i + 1])) {
                    dot++;
                    break;
                } else if (i == end) {
                    dot++;
                    break;
                } else if (i != 0 && s.size() > 2 && (isdigit(s[i - 1]) || s[i - 1] == '+' || s[i - 1] == '-') &&
                           (isdigit(s[i + 1]) || s[i + 1] == 'e' || s[i + 1] == 'E')) {
                    dot++;
                    break;
                } else return false;
            case ' ':
                break;
            default:
                return false;
        }
    }
    if ((e + E) > 1 || dot > 1 || num == 0) return false;
    return true;
}

int main() {
    cout<<isNumber(" 7e+6")<<endl;
    cout << isNumber("46.e3") << endl;
    cout << isNumber("+.8") << endl;
    cout << isNumber("0") << endl;
    cout << isNumber("1 ") << endl;
    cout << isNumber("3.") << endl;
    cout << isNumber(".1") << endl;
    cout << isNumber("-1E-16") << endl;
    cout << isNumber(". 1") << endl;
    cout << isNumber(".1.") << endl;
    cout << isNumber("12e") << endl;
    cout << isNumber("12e+5.4") << endl;
    cout<<isNumber("6e6.5")<<endl;
}