#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

char nextGreatestLetter(vector<char> &letters, char target) {
    int i = 0, j = letters.size() - 1;
    while (i <= j) {
        int mid = (j - i) / 2 + i;
        if(letters[mid] > target ){
            j = mid - 1;
        } else
            i = mid +1;
    }
    return letters[i%letters.size()];
}

int main(){
    vector<char> letters = {'c','f','j'};
    cout<<nextGreatestLetter(letters, 'a')<<endl;
    cout<<nextGreatestLetter(letters, 'c')<<endl;
    cout<<nextGreatestLetter(letters, 'j')<<endl;
    return 0;
}